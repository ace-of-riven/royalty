#include "../eng_texture.h"

Texture::Texture ( ) : _texture ( NULL ) {

}

Texture::Texture ( unsigned int w , unsigned int h , unsigned int channels , const float *data ) {
	switch ( channels ) {
		case 4:
			_texture = GPU_texture_create_2d ( w , h , eGPUTextureFormat::GPU_RGBA32F , data ) ;
			break;
		case 3:
			_texture = GPU_texture_create_2d ( w , h , eGPUTextureFormat::GPU_RGBA32F , data );
			break;
		default:
			_texture = NULL;
			printf ( "Texture is unsupposrted.\n" ) ;
	}
}

Texture::~Texture ( ) {
	if ( _texture )
		GPU_texture_free ( _texture ) ;
}
