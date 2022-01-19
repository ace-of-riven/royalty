#pragma once

/* GPU Types */
typedef enum eGPUDeviceType {
	GPU_DEVICE_NVIDIA = ( 1 << 0 ) ,
	GPU_DEVICE_ATI = ( 1 << 1 ) ,
	GPU_DEVICE_INTEL = ( 1 << 2 ) ,
	GPU_DEVICE_INTEL_UHD = ( 1 << 3 ) ,
	GPU_DEVICE_APPLE = ( 1 << 3 ) ,
	GPU_DEVICE_SOFTWARE = ( 1 << 4 ) ,
	GPU_DEVICE_UNKNOWN = ( 1 << 5 ) ,
	GPU_DEVICE_ANY = ( 0xff ) ,
} eGPUDeviceType;

typedef enum eGPUOSType {
	GPU_OS_WIN = ( 1 << 8 ) ,
	GPU_OS_MAC = ( 1 << 9 ) ,
	GPU_OS_UNIX = ( 1 << 10 ) ,
	GPU_OS_ANY = ( 0xff00 ) ,
} eGPUOSType;

typedef enum eGPUDriverType {
	GPU_DRIVER_OFFICIAL = ( 1 << 16 ) ,
	GPU_DRIVER_OPENSOURCE = ( 1 << 17 ) ,
	GPU_DRIVER_SOFTWARE = ( 1 << 18 ) ,
	GPU_DRIVER_ANY = ( 0xff0000 ) ,
} eGPUDriverType;

typedef enum eGPUSupportLevel {
	GPU_SUPPORT_LEVEL_SUPPORTED ,
	GPU_SUPPORT_LEVEL_LIMITED ,
	GPU_SUPPORT_LEVEL_UNSUPPORTED ,
} eGPUSupportLevel;

void GPU_platform_init ( );

bool GPU_type_matches ( eGPUDeviceType device , eGPUOSType os , eGPUDriverType driver );
eGPUSupportLevel GPU_platform_support_level ( void );
const char *GPU_platform_vendor ( void );
const char *GPU_platform_renderer ( void );
const char *GPU_platform_version ( void );
const char *GPU_platform_support_level_key ( void );
const char *GPU_platform_gpu_name ( void );

void GPU_platform_exit ( );

int GPU_max_texture_size ( void );
int GPU_max_texture_layers ( void );
int GPU_max_textures ( void );
int GPU_max_textures_frag ( void );
int GPU_max_textures_geom ( void );
int GPU_max_textures_vert ( void );
float GPU_max_texture_anisotropy ( void );
int GPU_max_color_texture_samples ( void );
int GPU_max_cube_map_size ( void );
int GPU_max_ubo_binds ( void );
int GPU_max_ubo_size ( void );
float GPU_max_line_width ( void );
void GPU_get_dfdy_factors ( float factors [ 2 ] );
bool GPU_arb_base_instance_is_supported ( void );
bool GPU_context_local_shaders_workaround ( void );
bool GPU_unused_fb_slot_workaround ( );
bool GPU_crappy_amd_driver ( void );

bool GPU_type_matches ( eGPUDeviceType device , eGPUOSType os , eGPUDriverType driver );

eGPUSupportLevel GPU_platform_support_level ( void );
const char *GPU_platform_support_level_key ( void );
const char *GPU_platform_gpu_name ( void );

