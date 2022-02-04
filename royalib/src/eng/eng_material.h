#pragma once

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

#include "eng_proctor.h"
#include "eng_texture.h"

class Material : public Proctor {
	GPU_Texture *albedo_t ;
	glm::vec4 albedo_c ;
public:
	Material ( ) ;
	~Material ( ) ;

	virtual int ComponentStack ( int comp );

	void SetAlbedo ( const Texture *albedo ) ;
	void SetAlbedo ( glm::vec4 colour ) ;
	void SetAlbedo ( const Texture *albedo , glm::vec4 colour ) ;

	inline GPU_Texture *GetAlbedoTexture ( ) const { return albedo_t; }
	inline glm::vec4 GetAlbedoColour ( ) const { return albedo_c; }
};
