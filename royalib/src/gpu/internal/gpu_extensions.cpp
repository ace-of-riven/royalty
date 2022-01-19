#include "../gpu_extensions.h"

bool GPU_mem_stats_supported (void) {
	return (GLEW_NVX_gpu_memory_info || GLEW_ATI_meminfo) ;
}

void GPU_mem_stats_get (int *totalmem, int *freemem) {
	/* TODO(merwin): use Apple's platform API to get this info */

	if (GLEW_NVX_gpu_memory_info) {
		/* returned value in Kb */
		glGetIntegerv (GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, totalmem);

		glGetIntegerv (GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, freemem);
	}
	else if (GLEW_ATI_meminfo) {
		int stats[4];

		glGetIntegerv (GL_TEXTURE_FREE_MEMORY_ATI, stats);
		*freemem = stats[0];
		*totalmem = 0;
	}
	else {
		*totalmem = 0;
		*freemem = 0;
	}
}

long long GPU_mem_stats_totalmem () {
	int totalmem , freemem ;
	GPU_mem_stats_get (&totalmem, &freemem);
	return 1024LL * totalmem ;
}

long long GPU_mem_stats_freemem () {
	int totalmem, freemem;
	GPU_mem_stats_get (&totalmem, &freemem);
	return 1024LL * freemem ;
}

unsigned int GPU_get_max_textures ( ) {
	int maxtexturesfrag;
	glGetIntegerv ( GL_MAX_TEXTURE_IMAGE_UNITS , &maxtexturesfrag );
	return maxtexturesfrag;
}
