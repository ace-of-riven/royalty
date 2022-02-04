#include "eng_staticobject.h"

static unsigned int staticobject_ids = 0x16;

int StaticObject::ComponentStack ( int comp ) {
	switch ( comp ) {
		case COMP_SCRIPT: return PROCTOR_MAX;
	}
	return 0;
}

StaticObject::StaticObject ( const std::string &name ) : id ( staticobject_ids++ ) , name ( name ) {
	batch = NULL;
}

void StaticObject::Begin ( ) {
	batch = ENG_ViewportRenderer->Begin ( batch ) ;
}

void StaticObject::Push ( const GameObject *object ) {
	const std::vector<Component *> *MeshList = object->GetComponents<Mesh> ( ) ;
	if ( MeshList )
		for ( auto mesh : *MeshList )
			ENG_ViewportRenderer->Append ( ( const Mesh * ) mesh );
}

void StaticObject::Push ( const Mesh *mesh ) {
	ENG_ViewportRenderer->Append ( mesh );
}

void StaticObject::End ( ) {
	ENG_ViewportRenderer->Finish ( ) ;
}

void StaticObject::OnUpdate ( double deltaTime ) {
	ENG_ViewportRenderer->Push ( batch ) ;
}
