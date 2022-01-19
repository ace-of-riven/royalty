#pragma once

#include <Windows.h>

#include "gpu_init.h"

#include <vector>
#include <set>

struct GPU_Context {
	unsigned int default_vao;
	unsigned int default_framebuffer;
	std::vector<unsigned int> orphaned_vertarray_ids;
	std::vector<unsigned int> orphaned_framebuffer_ids;

	/* Batches that have VAOs from this context */
	std::set<struct GPU_Batch *> batches;

	struct GPU_Framebuffer *current_fbo;

	struct GPU_MatrixState *matrix_state;

	class wxGLContext *wx_context;
	class wxGLCanvas *wx_canvas;

	struct GPU_Texture *invalid_tex_1D;
	struct GPU_Texture *invalid_tex_2D;
	struct GPU_Texture *invalid_tex_3D;

	struct GPU_Texture *empty_tex_1D;
	struct GPU_Texture *empty_tex_2D;
	struct GPU_Texture *empty_tex_3D;

	HGLRC handle;

	HWND owner;
};

GPU_Context *GPU_context_create ( HWND owner , GLuint default_framebuffer );
GPU_Context *GPU_context_create ( HWND owner );
GPU_Context *GPU_context_active_get ( void );
void GPU_context_active_set ( GPU_Context *ctx );

unsigned int GPU_vao_default ( void );
unsigned int GPU_framebuffer_default ( void );
unsigned int GPU_vao_alloc ( void );
unsigned int GPU_buf_alloc ( void );
unsigned int GPU_tex_alloc ( void );
unsigned int GPU_fbo_alloc ( void );

void GPU_vao_free ( unsigned int vao_id , GPU_Context *ctx );
void GPU_fbo_free ( unsigned int fbo_id , GPU_Context *ctx );
void GPU_buf_free ( unsigned int buf_id );
void GPU_tex_free ( unsigned int tex_id );

void gpu_context_active_framebuffer_set ( GPU_Context *ctx , struct GPU_Framebuffer *fb );
struct GPU_Framebuffer *gpu_context_active_framebuffer_get ( GPU_Context *ctx );

struct GPU_MatrixState *gpu_context_active_matrix_state_get ( void );

void gpu_context_add_batch ( GPU_Context *ctx , struct GPU_Batch *batch );
void gpu_context_remove_batch ( GPU_Context *ctx , struct GPU_Batch *batch );

void GPU_discard_context ( GPU_Context *ctx );
