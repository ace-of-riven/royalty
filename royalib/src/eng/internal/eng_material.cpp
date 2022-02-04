#include "../eng_material.h"

int Material::ComponentStack ( int comp ) {
	switch ( comp ) {
		case COMP_SCRIPT: return PROCTOR_MAX;
	}
	return 0;
}

Material::Material ( ) {
	albedo_t = GPU_texture_get_empty ( 2 ) ;
	albedo_c = glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) ;
}

Material::~Material ( ) {

}

void Material::SetAlbedo ( GPU_Texture *albedo ) {
	albedo_c = glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) ;
	if ( albedo )
		albedo_t = albedo;
	else
		albedo_t = GPU_texture_get_empty ( 2 );
}

void Material::SetAlbedo ( glm::vec4 colour ) {
	albedo_t = GPU_texture_get_empty ( 2 );
	albedo_c = colour;
}

void Material::SetAlbedo ( GPU_Texture *albedo , glm::vec4 colour ) {
	albedo_c = colour;
	if ( albedo )
		albedo_t = albedo;
	else
		albedo_t = GPU_texture_get_empty ( 2 );
}
