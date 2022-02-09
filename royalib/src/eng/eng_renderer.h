#pragma once

#include "eng_component.h"
#include "eng_proctor.h"
#include "eng_gameobject.h"
#include "eng_mesh.h"
#include "eng_script.h"
#include "eng_material.h"

#include "../gpu/gpu_init.h"
#include "../gpu/gpu_backend.h"
#include "../gpu/gpu_context.h"
#include "../gpu/gpu_texture.h"
#include "../gpu/gpu_batch.h"
#include "../gpu/gpu_framebuffer.h"
#include "../gpu/gpu_vertbuff.h"
#include "../gpu/gpu_element.h"
#include "../gpu/gpu_matrix.h"
#include "../gpu/gpu_primitive.h"
#include "../gpu/gpu_shader.h"
#include "../gpu/gpu_uniform_buffer.h"
#include "../gpu/gpu_vertformat.h"

#include "../base/base_file.h"

#define MAX_VERTICES				(512*1024)
#define MAX_INDICES				(512*1024)

#define MAX_MESHES				(512)
#define MAX_MATERIALS				(32)
#define MAX_BONES				(512)
#define MAX_LIGHTS				(512)

class RendererBatch;

class ViewportRenderer {
	GPU_Shader *ViewportBatchShader;

	GPU_UniformBuf *ViewportMeshProperties;
	GPU_UniformBuf *ViewportMatProperties;

	std::vector<RendererBatch *> Batches;
	std::vector<RendererBatch *> External;
public:
	ViewportRenderer ( ) ;
	~ViewportRenderer ( ) ;

	void Begin ( ) ;
	void Push ( const Mesh *mesh ) ;
	void Push ( RendererBatch *batch ) ;
	void Flush ( ) ;

	inline GPU_Shader *GetShader ( ) const { return ViewportBatchShader; }
};

extern ViewportRenderer *ENG_ViewportRenderer;
