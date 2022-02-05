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

typedef std::vector<ViewportRendererBatch *> ViewportBatch;

class ViewportRenderer {
	GPU_Shader *ViewportBatchShader;

	GPU_UniformBuf *ViewportMeshProperties;
	GPU_UniformBuf *ViewportMatProperties;

	std::vector<const ViewportRendererBatch *> External;
	std::vector<ViewportRendererBatch *> Batches;

	int aPos , aNorm , aUV , aMeshID;
protected:
	void Insert ( ViewportRendererBatch *batch , const Mesh *mesh ) ;
	void Build ( ViewportRendererBatch *batch ) ;
	void Render ( const ViewportRendererBatch *batch ) ;

	ViewportBatch *list;
public:
	ViewportRenderer ( ) ;
	~ViewportRenderer ( ) ;

	void Begin ( ) ;
	void Push ( const ViewportBatch *list ) ;
	void Push ( const ViewportRendererBatch *batch ) ;
	void Push ( const Mesh *mesh ) ;
	void Flush ( ) ;

	// call with NULL to get a new one
	ViewportBatch *Begin ( ViewportBatch *batch );
	void Append ( const Mesh *mesh ) ;
	void Finish ( void ) ;
};

extern ViewportRenderer *ENG_ViewportRenderer;
