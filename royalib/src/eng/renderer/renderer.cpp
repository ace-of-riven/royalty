#include "renderer.h"
#include "batch.h"

#include "../../base/base_file.h"

Renderer::Renderer ( ) {
	char defines [ 1024 ];
	sprintf_s ( defines , 1024 ,
		    "#define MAX_MESHES %d\n"
		    "#define MAX_BONES %d\n"
		    "#define MAX_MATERIALS %d\n"
		    "#define MAX_LIGHTS %d\n" , MAX_MESHES , MAX_BONES , MAX_MATERIALS , MAX_LIGHTS );

	char *ViewportBatchShader_VS = ( char * ) DNA_file_read ( "rc/internal/shaders/viewport_batch.vert" , NULL );
	char *ViewportBatchShader_FS = ( char * ) DNA_file_read ( "rc/internal/shaders/viewport_batch.frag" , NULL );

	viewport_shader = GPU_shader_create ( ViewportBatchShader_VS , ViewportBatchShader_FS , NULL , defines );

	free ( ViewportBatchShader_VS );
	free ( ViewportBatchShader_FS );

	ubo.mesh = GPU_uniformbuf_create ( MAX_MESHES * sizeof ( MeshProperties_UBO::Mesh ) , "MeshProperties" );
	ubo.material = GPU_uniformbuf_create ( MAX_MATERIALS * sizeof ( MatProperties_UBO::Material ) , "MaterialProperties" );
}

Renderer::~Renderer ( ) {
	for ( auto batch : batches ) {
		delete batch;
	}
}

void Renderer::Begin ( ) {
	for ( auto batch : batches ) {
		batch->Clear ( );
	}
	external.clear ( );
}

void Renderer::Submit ( const Mesh *mesh ) {
	int CurrentBatch = batches.size ( );

	for ( unsigned int i = 0; i < CurrentBatch; i++ )
		if ( batches [ i ]->HasSpaceForMesh ( mesh ) )
			CurrentBatch = i;

	// check if batch list filled
	if ( CurrentBatch == batches.size ( ) )
		batches.push_back ( new Batch ( GPU_PRIM_TRIS , viewport_shader ) );

	Batch *batch = batches [ CurrentBatch ]; // select the new one if there was one selected

	batch->InsertMesh ( mesh );
}

void Renderer::Submit ( Batch *batch ) {
	external.push_back ( batch );
}

void Renderer::Flush ( ) {
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	GPU_depth_test ( true );

	GPU_shader_use ( viewport_shader );

	for ( unsigned int i = 0; i < batches.size ( ); i++ ) {
		batches [ i ]->Upload ( ubo.mesh , ubo.material );
		batches [ i ]->Render ( ubo.mesh , ubo.material );
	}

	for ( unsigned int i = 0; i < external.size ( ); i++ ) {
		external [ i ]->Upload ( ubo.mesh , ubo.material );
		external [ i ]->Render ( ubo.mesh , ubo.material );
	}
}
