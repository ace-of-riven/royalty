#pragma once

#include "../../gpu/gpu_backend.h"
#include "../../gpu/gpu_batch.h"
#include "../../gpu/gpu_context.h"
#include "../../gpu/gpu_defs.h"
#include "../../gpu/gpu_element.h"
#include "../../gpu/gpu_extensions.h"
#include "../../gpu/gpu_framebuffer.h"
#include "../../gpu/gpu_init.h"
#include "../../gpu/gpu_matrix.h"
#include "../../gpu/gpu_primitive.h"
#include "../../gpu/gpu_shader.h"
#include "../../gpu/gpu_state.h"
#include "../../gpu/gpu_texture.h"
#include "../../gpu/gpu_uniform_buffer.h"
#include "../../gpu/gpu_vertbuff.h"
#include "../../gpu/gpu_vertformat.h"

#include "../core/mesh.h"

class Batch;

class Renderer {
	GPU_Shader *viewport_shader;

	struct {
		// mesh specific
		GPU_UniformBuf *mesh;

		// material specific
		GPU_UniformBuf *material;

		// environment / lights specific
		GPU_UniformBuf *light;
	} ubo ;

	std::vector<Batch *> batches;
	std::vector<Batch *> external;
public:
	Renderer ( ) ;
	~Renderer ( ) ;

	void Begin ( ) ;
	void Submit ( const Mesh *mesh ) ;
	void Submit ( Batch *external ) ;
	void Flush ( ) ;
};
