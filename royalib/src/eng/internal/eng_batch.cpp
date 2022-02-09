#include "eng_batch.h"

RendererBatch::RendererBatch ( GPUPrimType prim , GPU_Shader *shader ) : shader ( shader ) , prim ( prim ) {
	vbo = GPU_vertbuf_create ( GPUUsageType::GPU_USAGE_DYNAMIC );
	GPU_vertformat_from_interface ( &vbo->format , shader->shaderface );

	GPU_vertbuf_data_alloc ( vbo , MAX_VERTICES );

	builder = GPU_indexbuf_create_ex ( prim , MAX_INDICES , MAX_VERTICES );

	ibo = NULL;
	batch = NULL;

	vertices_count = 0;
	indices_count = 0;
	mesh_count = 0;

	aPos = GPU_vertformat_attr_id_get ( &vbo->format , "aPos" );
	aNorm = GPU_vertformat_attr_id_get ( &vbo->format , "aNorm" );
	aUV = GPU_vertformat_attr_id_get ( &vbo->format , "aUV" );
	aMeshID = GPU_vertformat_attr_id_get ( &vbo->format , "aMeshID" );

	transform = glm::mat4 ( 1.0f ) ;
}

RendererBatch::~RendererBatch ( ) {
	if ( batch )
		GPU_batch_discard ( batch ) ;
	if ( ibo )
		GPU_indexbuf_discard ( ibo ) ;
	if ( vbo )
		GPU_vertbuf_discard ( vbo );
	if ( builder->data )
		free ( builder->data ) ;
	if ( builder )
		delete builder;
}

// updates

void RendererBatch::Clear ( ) {
	mat_properties.data.clear ( ) ;
	mesh_properties.data.clear ( ) ;

	textures.clear ( );
	materials.clear ( );

	indices_count = 0;
	vertices_count = 0;
	mesh_count = 0;
}

void RendererBatch::InsertMesh ( const Mesh *mesh ) {
	unsigned int i_offset = vertices_count;

	int material_id = RegisterMaterial ( mesh->material );
	int albedo_tex_id = RegisterTexture ( mesh->material->GetAlbedoTexture ( ) );

	if ( mat_properties.data.size ( ) == material_id )
		mat_properties.data.push_back ( MatProperties_UBO::Material ( ) ) ;
	mat_properties.data [ material_id ].albedo_t = albedo_tex_id;
	mat_properties.data [ material_id ].albedo_c = mesh->material->GetAlbedoColour ( );

	if ( mesh_properties.data.size ( ) == mesh_count )
		mesh_properties.data.push_back ( MeshProperties_UBO::Mesh ( ) );
	mesh_properties.data [ mesh_count ].ModelView = mesh->transform.GetMatrix ( );
	mesh_properties.data [ mesh_count ].MaterialID = material_id;

	for ( unsigned int v = 0; v < mesh->GetVertices ( ).size ( ); v++ ) {
		if ( aPos + 1 )
			GPU_vertbuf_attr_set ( vbo , aPos , vertices_count , glm::value_ptr ( mesh->GetVertices ( ) [ v ].coord ) );
		if ( aUV + 1 )
			GPU_vertbuf_attr_set ( vbo , aUV , vertices_count , glm::value_ptr ( mesh->GetVertices ( ) [ v ].uv ) );
		if ( aNorm + 1 )
			GPU_vertbuf_attr_set ( vbo , aNorm , vertices_count , glm::value_ptr ( mesh->GetVertices ( ) [ v ].norm ) );
		if ( aMeshID + 1 )
			GPU_vertbuf_attr_set ( vbo , aMeshID , vertices_count , &mesh_count );
		vertices_count++;
	}

	for ( unsigned int i = 0; i < mesh->GetIndices ( ).size ( ); i++ ) {
		GPU_indexbuf_add_generic_vert ( builder , i_offset + mesh->GetIndices ( ) [ i ] );
		indices_count++;
	}

	mesh_count++;
}

void RendererBatch::Upload ( GPU_UniformBuf *mesh_ubo , GPU_UniformBuf *mat_ubo ) {
	if ( indices_count == 0 or vertices_count == 0 or mesh_count == 0 )
		return;

	// load the indices to the IndexBuffer

	if ( ibo ) {
		GPU_indexbuf_build_in_place ( builder , ibo );
	}
	else {
		ibo = GPU_indexbuf_build ( builder );

		batch = GPU_batch_create_ex ( prim , vbo , ibo , NULL );
		GPU_batch_program_set_shader ( batch , shader );
	}

	// we just unloaded the builder so we need to reset it

	{
		GPU_indexbuf_init_ex ( builder , prim , MAX_INDICES , MAX_VERTICES );
	}

	// update the uniform buffers with our own data

	if ( mesh_properties.data.size ( ) )
		GPU_uniformbuf_update ( mesh_ubo , 0 , &mesh_properties.data [ 0 ] , mesh_properties.data.size ( ) * sizeof ( MeshProperties_UBO::Mesh ) );
	if ( mat_properties.data.size ( ) )
		GPU_uniformbuf_update ( mat_ubo , 0 , &mat_properties.data [ 0 ] , mat_properties.data.size ( ) * sizeof ( MatProperties_UBO::Material ) );
}

void RendererBatch::Render ( GPU_UniformBuf *mesh_ubo , GPU_UniformBuf *mat_ubo ) const {
	if ( indices_count == 0 or vertices_count == 0 or mesh_count == 0 )
		return;

	GPU_uniformbuf_bind ( mesh_ubo , 1 );
	GPU_uniformbuf_bind ( mat_ubo , 0 );

	static char u_buffer [ 256 ];

	for ( unsigned int i = 0; i < textures.size ( ); i++ ) {
		sprintf_s ( u_buffer , 256 , "uTexture[%d]" , i );
		GPU_texture_bind ( textures [ i ] , i );
		GPU_batch_uniform_1i ( batch , u_buffer , i );
	}

	// Apply our transform without editing all the data in the uniform buffers
	GPU_matrix_push ( ) ;
	GPU_matrix_mul ( transform ) ;

	GPU_matrix_bind ( shader->shaderface );

	GPU_batch_draw_advanced ( batch , 0 , indices_count , 0 , 0 );

	GPU_matrix_pop ( ) ;
}

void RendererBatch::UpdateMatrix ( const glm::mat4 &matrix ) {
	transform = matrix;
}

int RendererBatch::RegisterTexture ( GPU_Texture *in ) {
	GPU_Texture *texture = ( in ) ? in : GPU_texture_get_empty ( 2 );
	int texture_id = textures.size ( );
	for ( unsigned int i = 0; i < texture_id; i++ )
		if ( textures [ i ] == texture )
			texture_id = i;
	if ( texture_id == textures.size ( ) )
		textures.push_back ( texture ) ;
	return texture_id ;
}

int RendererBatch::RegisterMaterial ( Material *material ) {
	int material_id = materials.size ( );
	for ( unsigned int i = 0; i < material_id; i++ )
		if ( materials [ i ] == material )
			material_id = i;
	if ( material_id == materials.size ( ) )
		materials.push_back ( material ) ;
	return material_id ;
}

// queries

bool RendererBatch::HasSpaceForTexture ( const GPU_Texture *in ) {
	const GPU_Texture *texture = ( in ) ? in : GPU_texture_get_empty ( 2 ) ;
	int texture_id = textures.size ( );
	for ( unsigned int i = 0; i < texture_id; i++ )
		if ( textures [ i ] == texture )
			texture_id = i;
	if ( texture_id < GPU_max_textures_frag ( ) )
		return true;
	return false;
}

bool RendererBatch::HasSpaceForMaterial ( const Material *material ) {
	int material_id = materials.size ( ) ;
	for ( unsigned int i = 0; i < material_id; i++ )
		if ( materials [ i ]->MaterialHash ( ) == material->MaterialHash ( ) )
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

bool RendererBatch::HasSpaceForMesh ( const Mesh *mesh ) {
	if ( vertices_count + mesh->GetVertices ( ).size ( ) >= MAX_VERTICES or
	     indices_count + mesh->GetIndices ( ).size ( ) >= MAX_INDICES or
	     mesh_count >= MAX_MESHES ) {
		return false;
	}
	return HasSpaceForMaterial ( mesh->material );
}
