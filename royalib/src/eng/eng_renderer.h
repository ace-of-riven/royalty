#pragma once

#include "eng_component.h"
#include "eng_proctor.h"
#include "eng_gameobject.h"
#include "eng_skeleton.h"
#include "eng_mesh.h"
#include "eng_script.h"
#include "eng_light.h"
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

#define MAX_MESHES				(256)
#define MAX_MATERIALS				(32)
#define MAX_BONES				(512)
#define MAX_LIGHTS				(512)

class RendererBatch;

struct LightProperties_UBO {
	struct Light {
		ALIGN_STD140 glm::vec3 location;		// light caster position
		ALIGN_STD140 glm::vec3 colour;			// light caster colour
		ALIGN_STD140 glm::vec3 attenuation;		// light caster attenuation
		ALIGN_STD140 glm::vec3 direction;		// light caster direction
		ALIGN_STD140 float cutOff;			// light cut off angle
		ALIGN_STD140 float outerCutOff;			// light outer cut off angle
	};
	ALIGN_STD140 int light_count;				// lights counter

	// add this to a vector so that everytime we copy this to the GPU we only copy the data that we actually need
	std::vector<Light> data;
};

class ViewportRenderer {
	GPU_Shader *ViewportBatchShader;

	LightProperties_UBO light_properties;

	GPU_UniformBuf *ViewportMeshProperties;
	GPU_UniformBuf *ViewportMatProperties;
	GPU_UniformBuf *ViewportLightProperties;

	std::vector<RendererBatch *> Batches;
	std::vector<RendererBatch *> External;
public:
	ViewportRenderer ( ) ;
	~ViewportRenderer ( ) ;

	void Begin ( ) ;
	void Push ( const Mesh *mesh ) ;
	void Push ( const Skeleton *skeleton , const Mesh *mesh ) ;
	void Push ( const Light *light ) ;
	void Push ( RendererBatch *batch ) ;
	void Flush ( ) ;

	inline GPU_Shader *GetShader ( ) const { return ViewportBatchShader; }
};

extern ViewportRenderer *ENG_ViewportRenderer;
