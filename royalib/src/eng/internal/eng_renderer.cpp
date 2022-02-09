#include "../eng_renderer.h"

#include "eng_batch.h"

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

	ViewportMeshProperties = GPU_uniformbuf_create ( MAX_MESHES * sizeof ( MeshProperties_UBO::Mesh ) , "MeshProperties" );
	ViewportMatProperties = GPU_uniformbuf_create ( MAX_MATERIALS * sizeof ( MatProperties_UBO::Material ) , "MaterialProperties" );
	ViewportLightProperties = GPU_uniformbuf_create ( 16 + MAX_LIGHTS * sizeof ( LightProperties_UBO::Light ) , "LightProperties" );
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

	light_properties.light_count = 0;
	light_properties.data.clear ( );

	External.clear ( ) ;
}

void ViewportRenderer::Push ( const Light *light ) {
	if ( light_properties.light_count + 1 < MAX_LIGHTS ) {
		LightProperties_UBO::Light l;
		l.location = light->transform.GetMatrix ( ) * glm::vec4 ( 0.0f , 0.0f , 0.0f , 1.0f );
		l.attenuation = light->GetAttenuation ( );
		l.colour = light->GetColour ( );
		l.direction = light->transform.GetMatrix ( ) * glm::vec4 ( 0.0f , 0.0f , -1.0f , 1.0f );
		l.cutOff = light->GetCutOffAngle ( );
		l.outerCutOff = light->GetOuterCutOffAngle ( );

		light_properties.data.push_back ( l ) ;
		light_properties.light_count++;
	}
}

void ViewportRenderer::Push ( const Mesh *mesh ) {
	int CurrentBatch = Batches.size ( ) ;

	for ( unsigned int i = 0; i < CurrentBatch; i++ )
		if ( Batches [ i ]->HasSpaceForMesh ( mesh ) )
			CurrentBatch = i ;

	// check if batch list filled
	if ( CurrentBatch == Batches.size ( ) )
		Batches.push_back ( new RendererBatch ( GPU_PRIM_TRIS , ViewportBatchShader ) );

	RendererBatch *batch = Batches [ CurrentBatch ]; // select the new one if there was one selected

	batch->InsertMesh ( mesh ) ;
}

void ViewportRenderer::Push ( RendererBatch *batch ) {
	External.push_back ( batch ) ;
}

void ViewportRenderer::Flush ( ) {
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) ;

	GPU_depth_test ( true ) ;

	GPU_shader_use ( ViewportBatchShader );

	GPU_uniformbuf_bind ( ViewportLightProperties , 2 );

	GPU_uniformbuf_update ( ViewportLightProperties , 0 , &light_properties.light_count , sizeof ( int ) );
	if ( light_properties.data.size ( ) )
		GPU_uniformbuf_update ( ViewportLightProperties , 16 , &light_properties.data [ 0 ] , light_properties.data.size ( ) * sizeof ( MeshProperties_UBO::Mesh ) );

	for ( unsigned int i = 0; i < Batches.size ( ); i++ ) {
		Batches [ i ]->Upload ( ViewportMeshProperties , ViewportMatProperties ) ;
		Batches [ i ]->Render ( ViewportMeshProperties , ViewportMatProperties ) ;
	}

	for ( unsigned int i = 0; i < External.size ( ); i++ ) {
		External [ i ]->Upload ( ViewportMeshProperties , ViewportMatProperties );
		External [ i ]->Render ( ViewportMeshProperties , ViewportMatProperties );
	}
}
