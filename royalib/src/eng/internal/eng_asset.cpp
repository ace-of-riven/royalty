#include "../eng_asset.h"

#include <stdlib.h> 
#include <stdio.h>
#include <map>

#include "../../../ext/stb-master/stb_image.h"

struct {
	std::map<std::string , Texture *> iTexture ;
} ImportedAssets ;

std::string ConvertPath ( const std::string &path ) {
	char Buffer [ 1024 ] ;
	GetFullPathNameA ( path.c_str ( ) , 1024 , Buffer , NULL ) ;
	return Buffer;
}

void ClearAllAssets ( ) {
	for ( auto texture : ImportedAssets.iTexture )
		delete texture.second ;
	ImportedAssets.iTexture.clear ( ) ;
}

Texture *ImportTexture ( const std::string &name ) {
	std::string real = ConvertPath ( name ) ;
	if ( ImportedAssets.iTexture.find ( real ) != ImportedAssets.iTexture.end ( ) )
		return ImportedAssets.iTexture [ real ] ;
	int width , height , channels;
	unsigned char *img = stbi_load ( real.c_str ( ) , &width , &height , &channels , 4 ) ;
	if ( img == NULL ) {
		printf ( "Error in loading the image\n" );
		return NULL;
	}
	Texture *out = ImportedAssets.iTexture [ real ] = new Texture ( width , height , channels , img ) ;
	free ( img ) ;
	return out ;
}
