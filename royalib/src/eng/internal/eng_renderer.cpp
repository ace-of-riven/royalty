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

	ViewportMeshProperties = GPU_uniformbuf_create ( MAX_MESHES * sizeof ( ViewportMeshProperties_UBO::Mesh ) , "MeshProperties" );
	ViewportMatProperties = GPU_uniformbuf_create ( MAX_MATERIALS * sizeof ( ViewportMatProperties_UBO::Material ) , "MaterialProperties" );
}

ViewportRenderer::~ViewportRenderer ( ) {
	for ( auto batch : Batches ) {
		delete batch;
	}
}

void ViewportRenderer::Begin ( ) {
	for ( auto batch : Batches ) {
		batch->Clear ( ) ;
	}
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

	batch->InsertMesh ( mesh ) ;
}

void ViewportRenderer::Flush ( ) {
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) ;

	GPU_depth_test ( true ) ;

	GPU_shader_use ( ViewportBatchShader );

	for ( unsigned int i = 0; i < Batches.size ( ); i++ ) {
		Batches [ i ]->Upload ( ViewportMeshProperties , ViewportMatProperties ) ;
		Batches [ i ]->Render ( ViewportMeshProperties , ViewportMatProperties ) ;
	}
}
