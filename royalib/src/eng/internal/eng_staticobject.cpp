#include "../eng_staticobject.h"

#include "eng_batch.h"

static unsigned int staticobject_ids = 0x12;

StaticObject::StaticObject ( ) : id ( staticobject_ids++ ) , name ( name ) {
}

StaticObject::~StaticObject ( ) {
}

void StaticObject::Push ( const GameObject *obj ) {
	auto vec = obj->GetComponents<Mesh> ( );
	if ( vec )
		for ( auto item : *vec )
			Push ( ( const Mesh * ) item ) ;
}

void StaticObject::Push ( const Mesh *obj ) {
	int CurrentBatch = batches.size ( );

	for ( unsigned int i = 0; i < CurrentBatch; i++ )
		if ( batches [ i ]->HasSpaceForMesh ( obj ) )
			CurrentBatch = i;

	// check if batch list filled
	if ( CurrentBatch == batches.size ( ) )
		batches.push_back ( new RendererBatch ( GPU_PRIM_TRIS , ENG_ViewportRenderer->GetShader ( ) ) ) ;

	batches [ CurrentBatch ]->InsertMesh ( obj );
}

void StaticObject::OnUpdate ( double deltaTime ) {
	for ( unsigned int i = 0; i < batches.size ( ); i++ )
		ENG_ViewportRenderer->Push ( batches [ i ] ) ;
}
