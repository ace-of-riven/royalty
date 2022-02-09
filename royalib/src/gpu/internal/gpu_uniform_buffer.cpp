#define _CRT_SECURE_NO_WARNINGS

#include "../gpu_uniform_buffer.h"
#include "../gpu_context.h"

static void GPU_uniformbuf_init ( GPU_UniformBuf* ubo ) {
	glGenBuffers ( 1 , &ubo->ubo_id );
	glBindBuffer ( GL_UNIFORM_BUFFER , ubo->ubo_id );
	glBufferData ( GL_UNIFORM_BUFFER , ubo->size_in_bytes , nullptr , GL_DYNAMIC_DRAW );
}

GPU_UniformBuf* GPU_uniformbuf_create ( size_t size , const char* name ) {
	GPU_UniformBuf* ubo = new GPU_UniformBuf ( );
	ubo->size_in_bytes = size;
	ubo->data = NULL ;
	strcpy ( ubo->name , name ) ;
	return ubo;
}

void GPU_uniformbuf_update ( GPU_UniformBuf* ubo , const void* data ) {
	if ( ubo->ubo_id == 0 ) {
		GPU_uniformbuf_init ( ubo );
	}
	glBindBuffer ( GL_UNIFORM_BUFFER , ubo->ubo_id );
	glBufferSubData ( GL_UNIFORM_BUFFER , 0 , ubo->size_in_bytes , data );
	glBindBuffer ( GL_UNIFORM_BUFFER , 0 );
}

void GPU_uniformbuf_update ( GPU_UniformBuf *ubo , size_t off , const void *data , size_t len ) {
	if ( ubo->ubo_id == 0 ) {
		GPU_uniformbuf_init ( ubo );
	}
	glBindBuffer ( GL_UNIFORM_BUFFER , ubo->ubo_id );
	glBufferSubData ( GL_UNIFORM_BUFFER , off , len , data );
	glBindBuffer ( GL_UNIFORM_BUFFER , 0 );
}

int GPU_uniformbuf_index ( GPU_UniformBuf* ubo , GPU_ShaderInterface* shaderface ) {
	return glGetUniformBlockIndex ( shaderface->program , ubo->name ) ;
}

int GPU_uniformbuf_index ( GPU_UniformBuf* ubo , GPU_Shader* shader ) {
	return glGetUniformBlockIndex ( shader->program , ubo->name );
}

void GPU_uniformbuf_bind ( GPU_UniformBuf* ubo , int slot ) {
	if ( ubo->ubo_id == 0 ) {
		GPU_uniformbuf_init ( ubo );
	}
	if ( ubo->data != nullptr ) {
		GPU_uniformbuf_update ( ubo , ubo->data );
		free ( ubo->data );
	}
	ubo->slot = slot;
	glBindBufferBase ( GL_UNIFORM_BUFFER , ubo->slot , ubo->ubo_id );
}

void GPU_uniformbuf_unbind ( GPU_UniformBuf* ubo ) {
	ubo->slot = 0;
}

void GPU_uniformbuf_discard ( GPU_UniformBuf* buff ) {
	free ( buff->data ) ;
	GPU_buf_free ( buff->ubo_id ) ;
	delete buff;
}
