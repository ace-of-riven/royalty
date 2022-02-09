#pragma once

#include "../ext_include.h"

#include "../gpu/gpu_texture.h"

class Texture {
	GPU_Texture *_texture;
public:
	Texture ( ) ;
	Texture ( unsigned int w , unsigned int h , unsigned int channels , const unsigned char *data ) ;
	~Texture ( ) ;

	inline GPU_Texture *GetGPUTexture ( ) const {
		if ( _texture )
			return _texture;
		return GPU_texture_get_empty ( 2 ) ;
	}
};
