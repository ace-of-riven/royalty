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

#define MAX_VERTICES				(64*1024)
#define MAX_INDICES				(64*1024)

#define MAX_MESHES				(512)
#define MAX_MATERIALS				(64)
#define MAX_BONES				(512)
#define MAX_LIGHTS				(512)

struct ViewportRendererBatch;

class ViewportRenderer {
	GPU_Shader *ViewportBatchShader;

	GPU_UniformBuf *ViewportMeshProperties;
	GPU_UniformBuf *ViewportMatProperties;

	std::vector<ViewportRendererBatch *> Batches;
public:
	ViewportRenderer ( ) ;
	~ViewportRenderer ( ) ;

	void Begin ( ) ;
	void Push ( const Mesh *mesh ) ;
	void Flush ( ) ;
};

extern ViewportRenderer *ENG_ViewportRenderer;
