#include "../eng_renderer.h"

#include "eng_viewportbatch.h"

ViewportRenderer *ENG_ViewportRenderer;

ViewportRenderer::ViewportRenderer ( ) {
	char defines [ 1024 ] ;
	sprintf_s ( defines , 1024 ,
		    "#define MAX_MESHES %d\n"
		    "#define MAX_BONES %d\n"
		    "#define MAX_MATERIALS %d\n"
		    "#define MAX_LIGHTS %d\n" , MAX_MESHES , MAX_BONES , MAX_MATERIALS , MAX_LIGHTS );

	char *ViewportBatchShader_VS = ( char * ) DNA_file_read ( "rc/internal/shaders/viewport_batch.vert" , NULL );
	char *ViewportBatchShader_FS = ( char * ) DNA_file_read ( "rc/internal/shaders/viewport_batch.frag" , NULL );

	ViewportBatchShader = GPU_shader_create ( ViewportBatchShader_VS , ViewportBatchShader_FS , NULL , defines ) ;

	free ( ViewportBatchShader_VS ) ;
	free ( ViewportBatchShader_FS ) ;

	GPU_VertFormat *format = new GPU_VertFormat ( ) ;

	GPU_vertformat_from_interface ( format , ViewportBatchShader->shaderface ) ;
	aPos = GPU_vertformat_attr_id_get ( format , "aPos" );
	aNorm = GPU_vertformat_attr_id_get ( format , "aNorm" );
	aUV = GPU_vertformat_attr_id_get ( format , "aUV" );
	aMeshID = GPU_vertformat_attr_id_get ( format , "aMeshID" );

	ViewportMeshProperties = GPU_uniformbuf_create ( sizeof ( ViewportMeshProperties_UBO ) , "MeshProperties" );
	ViewportMatProperties = GPU_uniformbuf_create ( sizeof ( ViewportMatProperties_UBO ) , "MaterialProperties" );

	delete format;
}

ViewportRenderer::~ViewportRenderer ( ) {

}

void ViewportRenderer::Begin ( ) {
	for ( auto batch : Batches ) {
		batch->textures.clear ( );
		batch->materials.clear ( );

		batch->indices_count = 0;
		batch->vertices_count = 0;
		batch->mesh_count = 0;
	}

	External.clear ( ) ;
}

void ViewportRenderer::Insert ( ViewportRendererBatch *batch , const Mesh *mesh ) {
	unsigned int i_offset = batch->vertices_count;

	int material_id = batch->RegisterMaterial ( mesh->material );
	int albedo_tex_id = batch->RegisterTexture ( mesh->material->GetAlbedoTexture ( ) ) ;

	batch->mat_properties.Material [ material_id ].albedo_t = albedo_tex_id;
	batch->mat_properties.Material [ material_id ].albedo_c = mesh->material->GetAlbedoColour ( ) ;

	batch->mesh_properties.Mesh [ batch->mesh_count ].ModelView = mesh->transform.GetMatrix ( );
	batch->mesh_properties.Mesh [ batch->mesh_count ].MaterialID = material_id;

	for ( unsigned int v = 0; v < mesh->GetVertices ( ).size ( ); v++ ) {
		if ( aPos + 1 )
			GPU_vertbuf_attr_set ( batch->vbo , aPos , batch->vertices_count , glm::value_ptr ( mesh->GetVertices ( ) [ v ].coord ) );
		if ( aUV + 1 )
			GPU_vertbuf_attr_set ( batch->vbo , aUV , batch->vertices_count , glm::value_ptr ( mesh->GetVertices ( ) [ v ].uv ) );
		if ( aNorm + 1 )
			GPU_vertbuf_attr_set ( batch->vbo , aNorm , batch->vertices_count , glm::value_ptr ( mesh->GetVertices ( ) [ v ].norm ) );
		if ( aMeshID + 1 )
			GPU_vertbuf_attr_set ( batch->vbo , aMeshID , batch->vertices_count , &batch->mesh_count );
		batch->vertices_count++;
	}

	for ( unsigned int i = 0; i < mesh->GetIndices ( ).size ( ); i++ ) {
		GPU_indexbuf_add_generic_vert ( batch->builder , i_offset + mesh->GetIndices ( ) [ i ] );
		batch->indices_count++;
	}  

	batch->mesh_count++;
}

void ViewportRenderer::Push ( const Mesh *mesh ) {
	int CurrentBatch = Batches.size ( ) ;

	for ( unsigned int i = 0; i < CurrentBatch; i++ )
		if ( Batches [ i ]->HasSpaceForMesh ( mesh ) )
			CurrentBatch = i ;

	// check if batch list filled
	if ( CurrentBatch == Batches.size ( ) )
		Batches.push_back ( new ViewportRendererBatch ( ViewportBatchShader ) );

	ViewportRendererBatch *batch = Batches [ CurrentBatch ]; // select the new one if there was one selected

	Insert ( batch , mesh ) ;
}

void ViewportRenderer::Push ( const ViewportRendererBatch *batch ) {
	External.push_back ( batch ) ;
}

void ViewportRenderer::Push ( const ViewportBatch *list ) {
	for ( auto batch : *list )
		External.push_back ( batch );
}

void ViewportRenderer::Build ( ViewportRendererBatch *batch ) {
	if ( batch->ibo ) {
		GPU_indexbuf_build_in_place ( batch->builder , batch->ibo );
	}
	else {
		batch->ibo = GPU_indexbuf_build ( batch->builder );

		batch->batch = GPU_batch_create_ex ( GPU_PRIM_TRIS , batch->vbo , batch->ibo , NULL );
		GPU_batch_program_set_shader ( batch->batch , ViewportBatchShader );
	}

	// we just unloaded the builder so we need to get rid of it and create a new one

	{
		assert ( batch->builder->data == NULL );
		delete batch->builder;

		batch->builder = GPU_indexbuf_create_ex ( GPUPrimType::GPU_PRIM_TRIS , MAX_INDICES , MAX_VERTICES );
	}
}

void ViewportRenderer::Render ( const ViewportRendererBatch *batch ) {
	if ( batch->indices_count == 0 or batch->vertices_count == 0 or batch->mesh_count == 0 )
		return;

	GPU_shader_use ( ViewportBatchShader );

	GPU_uniformbuf_update ( ViewportMeshProperties , &batch->mesh_properties );
	GPU_uniformbuf_update ( ViewportMatProperties , &batch->mat_properties );

	GPU_uniformbuf_bind ( ViewportMeshProperties , 1 );
	GPU_uniformbuf_bind ( ViewportMatProperties , 0 );

	static char u_buffer [ 256 ] ;

	for ( unsigned int i = 0; i < batch->textures.size ( ); i++ ) {
		sprintf_s ( u_buffer , 256 , "uTexture[%d]" , i ) ;
		GPU_texture_bind ( batch->textures [ i ] , i ) ;
		GPU_batch_uniform_1i ( batch->batch , u_buffer , i ) ;
	}

	GPU_matrix_bind ( ViewportBatchShader->shaderface );

	GPU_batch_draw_advanced ( batch->batch , 0 , batch->indices_count , 0 , 0 );
}

void ViewportRenderer::Flush ( ) {
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) ;

	GPU_depth_test ( true ) ;

	for ( unsigned int i = 0; i < Batches.size ( ); i++ ) {
		Build ( Batches [ i ] ) ;
		Render ( Batches [ i ] ) ;
	}
	for ( unsigned int i = 0; i < External.size ( ); i++ ) {
		Render ( External [ i ] );
	}
}

//

ViewportBatch *ViewportRenderer::Begin ( ViewportBatch *in ) {
	list = ( in ) ? in : new ViewportBatch ( ) ;
	for ( auto batch : *list ) {
		batch->textures.clear ( );

		batch->indices_count = 0;
		batch->vertices_count = 0;
		batch->mesh_count = 0;
	}
	return list;
}

void ViewportRenderer::Append ( const Mesh *mesh ) {
	assert ( list ) ;

	int CurrentBatch = list->size ( );

	for ( unsigned int i = 0; i < CurrentBatch; i++ )
		if ( list->at ( i )->HasSpaceForMesh ( mesh ) )
			CurrentBatch = i;

	// check if batch list filled
	if ( CurrentBatch == list->size ( ) )
		list->push_back ( new ViewportRendererBatch ( ViewportBatchShader ) );

	ViewportRendererBatch *batch = list->at ( CurrentBatch ); // select the new one if there was one selected

	Insert ( batch , mesh ) ;
}

void ViewportRenderer::Finish ( void ) {
	for ( auto batch : *list )
		Build ( batch ) ;
	list = NULL;
}
