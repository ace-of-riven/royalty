#pragma once

#include "gpu_init.h"
#include "gpu_vertformat.h"

#include "gpu_shader.h"

struct GPU_UniformBuf {
	/** Data size in bytes. */
	size_t size_in_bytes;
	/** Continuous memory block to copy to GPU. This data is owned by the UniformBuf. */
	void* data = NULL;
	/** Debugging name */
	char name [ DEBUG_NAME_LEN ];
	/** Slot to which this UBO is currently bound. -1 if not bound. */
	int slot = -1;
	/** OpenGL Object handle. */
	GLuint ubo_id = 0;
};

GPU_UniformBuf *GPU_uniformbuf_create ( size_t size , const char *name );

int GPU_uniformbuf_index ( GPU_UniformBuf *ubo , GPU_Shader *shader );

void GPU_uniformbuf_update ( GPU_UniformBuf *ubo , const void* data ) ;
void GPU_uniformbuf_update ( GPU_UniformBuf *ubo , size_t off , const void *data , size_t len ) ;
void GPU_uniformbuf_bind ( GPU_UniformBuf* ubo , int slot ) ;
void GPU_uniformbuf_unbind ( GPU_UniformBuf* ubo ) ;

void GPU_uniformbuf_discard ( GPU_UniformBuf *buff );
