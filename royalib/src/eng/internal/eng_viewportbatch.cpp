#include "eng_viewportbatch.h"

ViewportRendererBatch::ViewportRendererBatch ( GPU_Shader *shader ) {
	vbo = GPU_vertbuf_create ( GPUUsageType::GPU_USAGE_DYNAMIC );
	GPU_vertformat_from_interface ( &vbo->format , shader->shaderface );

	GPU_vertbuf_data_alloc ( vbo , MAX_VERTICES );

	builder = GPU_indexbuf_create_ex ( GPUPrimType::GPU_PRIM_TRIS , MAX_INDICES , MAX_VERTICES );

	ibo = NULL;
	batch = NULL;

	vertices_count = 0;
	indices_count = 0;
	mesh_count = 0;
}

// updates

int ViewportRendererBatch::RegisterTexture ( GPU_Texture *in ) {
	GPU_Texture *texture = ( in ) ? in : GPU_texture_get_empty ( 2 );
	int texture_id = textures.size ( );
	for ( unsigned int i = 0; i < texture_id; i++ )
		if ( textures [ i ] == texture )
			texture_id = i;
	if ( texture_id == textures.size ( ) )
		textures.push_back ( texture ) ;
	return texture_id ;
}

int ViewportRendererBatch::RegisterMaterial ( Material *material ) {
	int material_id = materials.size ( );
	for ( unsigned int i = 0; i < material_id; i++ )
		if ( materials [ i ] == material )
			material_id = i;
	if ( material_id == materials.size ( ) )
		materials.push_back ( material ) ;
	return material_id ;
}

// queries

bool ViewportRendererBatch::HasSpaceForTexture ( const GPU_Texture *in ) {
	const GPU_Texture *texture = ( in ) ? in : GPU_texture_get_empty ( 2 ) ;
	int texture_id = textures.size ( );
	for ( unsigned int i = 0; i < texture_id; i++ )
		if ( textures [ i ] == texture )
			texture_id = i;
	if ( texture_id < GPU_max_textures_frag ( ) )
		return true;
	return false;
}

bool ViewportRendererBatch::HasSpaceForMaterial ( const Material *material ) {
	int material_id = materials.size ( ) ;
	for ( unsigned int i = 0; i < material_id; i++ )
		if ( materials [ i ] == material )
			material_id = i;
	// we are gonna have to insert a new one, make sure we have enough empty texture slots
	if ( material_id == materials.size ( ) ) {
		if ( HasSpaceForTexture ( material->GetAlbedoTexture ( ) ) == false )
			return false;
	}
	// make sure that if we have to add a new one we have the space for it
	if ( material_id < MAX_MATERIALS )
		return true;
	return false;
}

bool ViewportRendererBatch::HasSpaceForMesh ( const Mesh *mesh ) {
	if ( vertices_count + mesh->GetVertices ( ).size ( ) >= MAX_VERTICES or
	     indices_count + mesh->GetIndices ( ).size ( ) >= MAX_INDICES or
	     mesh_count >= MAX_MESHES ) {
		return false;
	}
	return HasSpaceForMaterial ( mesh->material );
}
