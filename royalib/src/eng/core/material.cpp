#include "material.h"

#include "../../base/base_hash.h"

Material::Material ( ) {
	albedo_t = GPU_texture_get_empty ( 2 );
	albedo_c = glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f );
	UpdateHash ( );
}

Material::~Material ( ) {

}

void Material::UpdateHash ( ) {
	float data [ ] = { albedo_t->bindcode , albedo_c.r, albedo_c.g, albedo_c.b , albedo_c.a };
	hash = DNA_hash_buffer32 ( data , 5 * sizeof ( int ) );
}

void Material::SetAlbedo ( GPU_Texture *albedo ) {
	albedo_c = glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f );
	if ( albedo )
		albedo_t = albedo;
	else
		albedo_t = GPU_texture_get_empty ( 2 );
	UpdateHash ( );
}

void Material::SetAlbedo ( glm::vec4 colour ) {
	albedo_t = GPU_texture_get_empty ( 2 );
	albedo_c = colour;
	UpdateHash ( );
}

void Material::SetAlbedo ( GPU_Texture *albedo , const glm::vec4& colour ) {
	albedo_c = colour;
	if ( albedo )
		albedo_t = albedo;
	else
		albedo_t = GPU_texture_get_empty ( 2 );
	UpdateHash ( );
}
