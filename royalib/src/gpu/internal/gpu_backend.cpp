#include <assert.h>

#include "../gpu_init.h"
#include "../gpu_backend.h"

#include "../../base/base_dynstr.h"
#include "../../base/base_string.h"

#include <malloc.h>
#include <stdio.h>

struct __GPUGLEWExtensions__ {
	GLint maxtexsize;
	GLint maxtexlayers;
	GLint maxcubemapsize;
	GLint maxtextures;
	GLint maxtexturesfrag;
	GLint maxtexturesgeom;
	GLint maxtexturesvert;
	GLint maxubosize;
	GLint maxubobinds;

	int samples_color_texture_max;

	float line_width_range [ 2 ];
	float max_anisotropy;

	char *vendor;
	char *version;
	char *renderer;

};

struct __GPUPlatformGlobal__ {
	bool initialized;

	eGPUSupportLevel support_level;
	long device;
	long os;
	long driver;

	char *support_key;
	char *gpu_name;

	float dfdyfactors [ 2 ];

	bool glew_arb_base_instance_is_supported;
	bool context_local_shaders_workaround;
	bool unused_fb_slot_workaround;

	char *vendor;
	char *renderer;
	char *version;
};

static __GPUGLEWExtensions__ GPUGLEWExtensions;
static __GPUPlatformGlobal__ GPUPlatformGlobal;

static char *create_key ( eGPUSupportLevel support_level , const char *vendor , const char *renderer , const char *version ) {
	DynStr *ds = BASE_dynstr_new ( );
	BASE_dynstr_appendf ( ds , "{%s/%s/%s}=" , vendor , renderer , version );
	if ( support_level == GPU_SUPPORT_LEVEL_SUPPORTED )
		BASE_dynstr_append ( ds , "SUPPORTED" );
	else if ( support_level == GPU_SUPPORT_LEVEL_LIMITED )
		BASE_dynstr_append ( ds , "LIMITED" );
	else
		BASE_dynstr_append ( ds , "UNSUPPORTED" );
	char *support_key = BASE_dynstr_get_cstring ( ds );
	BASE_dynstr_free ( ds );
	return support_key;
}

static char *create_gpu_name ( const char *vendor , const char *renderer , const char *version ) {
	DynStr *ds = BASE_dynstr_new ( );
	BASE_dynstr_appendf ( ds , "%s %s %s" , vendor , renderer , version );

	char *gpu_name = BASE_dynstr_get_cstring ( ds );
	BASE_dynstr_free ( ds );
	return gpu_name;
}

void GPU_platform_init ( ) {
	GPUPlatformGlobal.initialized = true;

	const char *vendor = ( const char * ) glGetString ( GL_VENDOR );
	const char *renderer = ( const char * ) glGetString ( GL_RENDERER );
	const char *version = ( const char * ) glGetString ( GL_VERSION );
	eGPUSupportLevel support_level = GPU_SUPPORT_LEVEL_SUPPORTED;
	long device = GPU_DEVICE_ANY;
	long os = GPU_OS_ANY;
	long driver = GPU_DRIVER_ANY;

	glGetIntegerv ( GL_MAX_TEXTURE_IMAGE_UNITS , &GPUGLEWExtensions.maxtexturesfrag );
	glGetIntegerv ( GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS , &GPUGLEWExtensions.maxtexturesvert );
	glGetIntegerv ( GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS , &GPUGLEWExtensions.maxtexturesgeom );
	glGetIntegerv ( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS , &GPUGLEWExtensions.maxtextures );
	glGetIntegerv ( GL_MAX_TEXTURE_SIZE , &GPUGLEWExtensions.maxtexsize );
	glGetIntegerv ( GL_MAX_ARRAY_TEXTURE_LAYERS , &GPUGLEWExtensions.maxtexlayers );
	glGetIntegerv ( GL_MAX_CUBE_MAP_TEXTURE_SIZE , &GPUGLEWExtensions.maxcubemapsize );

	if ( GLEW_EXT_texture_filter_anisotropic ) {
		glGetFloatv ( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT , &GPUGLEWExtensions.max_anisotropy );
	}
	else {
		GPUGLEWExtensions.max_anisotropy = 1.0f;
	}

	glGetIntegerv ( GL_MAX_FRAGMENT_UNIFORM_BLOCKS , &GPUGLEWExtensions.maxubobinds );
	glGetIntegerv ( GL_MAX_UNIFORM_BLOCK_SIZE , &GPUGLEWExtensions.maxubosize );
	glGetFloatv ( GL_ALIASED_LINE_WIDTH_RANGE , GPUGLEWExtensions.line_width_range );
	glGetIntegerv ( GL_MAX_COLOR_TEXTURE_SAMPLES , &GPUGLEWExtensions.samples_color_texture_max );

#ifdef _WIN32
	os = GPU_OS_WIN;
#elif defined(__APPLE__)
	os = GPU_OS_MAC;
#else
	os = GPU_OS_UNIX;
#endif

	if ( strstr ( vendor , "ATI" ) || strstr ( vendor , "AMD" ) ) {
		device = GPU_DEVICE_ATI;
		driver = GPU_DRIVER_OFFICIAL;
	}
	else if ( strstr ( vendor , "NVIDIA" ) ) {
		device = GPU_DEVICE_NVIDIA;
		driver = GPU_DRIVER_OFFICIAL;
	}
	else if ( strstr ( vendor , "Intel" ) ||
		/* src/mesa/drivers/dri/intel/intel_context.c */
		strstr ( renderer , "Mesa DRI Intel" ) || strstr ( renderer , "Mesa DRI Mobile Intel" ) ) {
		device = GPU_DEVICE_INTEL;
		driver = GPU_DRIVER_OFFICIAL;

		if ( strstr ( renderer , "UHD Graphics" ) ||
		     /* Not UHD but affected by the same bugs. */
		     strstr ( renderer , "HD Graphics 530" ) || strstr ( renderer , "Kaby Lake GT2" ) ||
		     strstr ( renderer , "Whiskey Lake" ) ) {
			device |= GPU_DEVICE_INTEL_UHD;
		}
	}
	else if ( strstr ( renderer , "Mesa DRI R" ) ||
		  ( strstr ( renderer , "Radeon" ) && strstr ( vendor , "X.Org" ) ) ||
		  ( strstr ( renderer , "AMD" ) && strstr ( vendor , "X.Org" ) ) ||
		  ( strstr ( renderer , "Gallium " ) && strstr ( renderer , " on ATI " ) ) ||
		  ( strstr ( renderer , "Gallium " ) && strstr ( renderer , " on AMD " ) ) ) {
		device = GPU_DEVICE_ATI;
		driver = GPU_DRIVER_OPENSOURCE;
	}
	else if ( strstr ( renderer , "Nouveau" ) || strstr ( vendor , "nouveau" ) ) {
		device = GPU_DEVICE_NVIDIA;
		driver = GPU_DRIVER_OPENSOURCE;
	}
	else if ( strstr ( vendor , "Mesa" ) ) {
		device = GPU_DEVICE_SOFTWARE;
		driver = GPU_DRIVER_SOFTWARE;
	}
	else if ( strstr ( vendor , "Microsoft" ) ) {
		device = GPU_DEVICE_SOFTWARE;
		driver = GPU_DRIVER_SOFTWARE;
	}
	else if ( strstr ( vendor , "Apple" ) ) {
		/* Apple Silicon. */
		device = GPU_DEVICE_APPLE;
		driver = GPU_DRIVER_OFFICIAL;
	}
	else if ( strstr ( renderer , "Apple Software Renderer" ) ) {
		device = GPU_DEVICE_SOFTWARE;
		driver = GPU_DRIVER_SOFTWARE;
	}
	else if ( strstr ( renderer , "llvmpipe" ) || strstr ( renderer , "softpipe" ) ) {
		device = GPU_DEVICE_SOFTWARE;
		driver = GPU_DRIVER_SOFTWARE;
	}
	else {
		printf ( "Warning: Could not find a matching GPU name. Things may not behave as expected.\n" );
		printf ( "Detected OpenGL configuration:\n" );
		printf ( "Vendor: %s\n" , vendor );
		printf ( "Renderer: %s\n" , renderer );
	}

	/* Detect support level */
	if ( ( device & GPU_DEVICE_INTEL ) && ( os & GPU_OS_WIN ) ) {
		/* Old Intel drivers with known bugs that cause material properties to crash.
		 * Version Build 10.18.14.5067 is the latest available and appears to be working
		 * ok with our workarounds, so excluded from this list. */
		if ( strstr ( version , "Build 7.14" ) || strstr ( version , "Build 7.15" ) ||
			strstr ( version , "Build 8.15" ) || strstr ( version , "Build 9.17" ) ||
			strstr ( version , "Build 9.18" ) || strstr ( version , "Build 10.18.10.3" ) ||
			strstr ( version , "Build 10.18.10.4" ) || strstr ( version , "Build 10.18.10.5" ) ||
			strstr ( version , "Build 10.18.14.4" ) ) {
			support_level = GPU_SUPPORT_LEVEL_LIMITED;
		}
	}
	if ( ( device & GPU_DEVICE_ATI ) && ( os & GPU_OS_UNIX ) ) {
		/* Platform seems to work when SB backend is disabled. This can be done
		 * by adding the environment variable `R600_DEBUG=nosb`. */
		if ( strstr ( renderer , "AMD CEDAR" ) ) {
			support_level = GPU_SUPPORT_LEVEL_LIMITED;
		}
	}
	
	GPUPlatformGlobal.device = device;
	GPUPlatformGlobal.os = os;
	GPUPlatformGlobal.driver = driver;
	GPUPlatformGlobal.support_level = support_level;
	
	GPUPlatformGlobal.vendor = BASE_strdup ( vendor );
	GPUPlatformGlobal.renderer = BASE_strdup ( renderer );
	GPUPlatformGlobal.version = BASE_strdup ( version );
	GPUPlatformGlobal.support_key = create_key ( support_level , vendor , vendor , version );
	GPUPlatformGlobal.gpu_name = create_gpu_name ( vendor , vendor , version );
}

void GPU_platform_exit ( ) {
	free ( GPUPlatformGlobal.vendor ) ;
	free ( GPUPlatformGlobal.renderer ) ;
	free ( GPUPlatformGlobal.version ) ;
	free ( GPUPlatformGlobal.support_key ) ;
	free ( GPUPlatformGlobal.gpu_name ) ;
	GPUPlatformGlobal.initialized = false;
}

int GPU_max_texture_size ( void ) {
	return GPUGLEWExtensions.maxtexsize;
}
int GPU_max_texture_layers ( void ) {
	return GPUGLEWExtensions.maxtexlayers;
}
int GPU_max_textures ( void ) {
	return GPUGLEWExtensions.maxtextures;
}
int GPU_max_textures_frag ( void ) {
	return GPUGLEWExtensions.maxtexturesfrag;
}
int GPU_max_textures_geom ( void ) {
	return GPUGLEWExtensions.maxtexturesgeom;
}
int GPU_max_textures_vert ( void ) {
	return GPUGLEWExtensions.maxtexturesvert;
}
float GPU_max_texture_anisotropy ( void ) {
	return GPUGLEWExtensions.max_anisotropy;
}
int GPU_max_color_texture_samples ( void ) {
	return GPUGLEWExtensions.samples_color_texture_max;
}
int GPU_max_cube_map_size ( void ) {
	return GPUGLEWExtensions.maxcubemapsize;
}
int GPU_max_ubo_binds ( void ) {
	return GPUGLEWExtensions.maxubobinds;
}
int GPU_max_ubo_size ( void ) {
	return GPUGLEWExtensions.maxubosize;
}
float GPU_max_line_width ( void ) {
	return GPUGLEWExtensions.line_width_range [ 1 ];
}
void GPU_get_dfdy_factors ( float factors [ 2 ] ) {
	memcpy ( factors , GPUPlatformGlobal.dfdyfactors , sizeof ( float ) * 2 );
}
bool GPU_arb_base_instance_is_supported ( void ) {
	return GPUPlatformGlobal.glew_arb_base_instance_is_supported;
}
bool GPU_context_local_shaders_workaround ( void ) {
	return GPUPlatformGlobal.context_local_shaders_workaround;
}
bool GPU_unused_fb_slot_workaround ( ) {
	return GPUPlatformGlobal.unused_fb_slot_workaround;
}
bool GPU_crappy_amd_driver ( void ) {
	/* Currently are the same drivers with the `unused_fb_slot` problem. */
	return GPU_unused_fb_slot_workaround ( );
}

bool GPU_type_matches ( eGPUDeviceType device , eGPUOSType os , eGPUDriverType driver ) {
	return ( GPUPlatformGlobal.device & device ) &&
		( GPUPlatformGlobal.os & os ) &&
		( GPUPlatformGlobal.driver & driver );
}

eGPUSupportLevel GPU_platform_support_level ( void ) {
	return GPUPlatformGlobal.support_level;
}
const char *GPU_platform_support_level_key ( void ) {
	return GPUPlatformGlobal.support_key;
}
const char *GPU_platform_gpu_name ( void ) {
	return GPUPlatformGlobal.gpu_name;
}
