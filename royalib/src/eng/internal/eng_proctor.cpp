#include "../eng_proctor.h"
#include "../eng_manager.h"

#include "../eng_mesh.h"
#include "../eng_script.h"

Proctor::Proctor ( ) {
	ENG_Royalty->Register ( this ) ;
}

Proctor::~Proctor ( ) {
	for ( auto &component_type : components ) {
		for ( auto &component : component_type.second ) {
			component->Destroy ( ) ;
			delete component;
		}
	}
	ENG_Royalty->Destroy ( this );
}

int Proctor::ComponentStack ( int comp ) {
	switch ( comp ) {
		case COMP_SCRIPT: return PROCTOR_MAX;
	}
	return 0;
}

void Proctor::Update ( double deltaTime ) {
	for ( auto &component_type : components ) {
		for ( auto &component : component_type.second ) {
			component->Update ( deltaTime );
		}
	}
	OnUpdate ( deltaTime );
}

void Proctor::Push ( Component *component ) {
	auto itr = std::find ( components [ component->Identifier ( ) ].begin ( ) , components [ component->Identifier ( ) ].end ( ) , component );

	// if this component doesnt already exist in us
	if ( itr == components [ component->Identifier ( ) ].end ( ) ) {
		if ( components [ component->Identifier ( ) ].size ( ) < ComponentStack ( component->Identifier ( ) ) ) {
			components [ component->Identifier ( ) ].push_back ( component );
		}
		else {
			printf ( "Too many %d components in proctor %p\n" , component->Identifier ( ) , this );
		}
	}

	component->Attach ( this );
}

void Proctor::Pop ( Component *component ) {
	auto T = component->Identifier ( );
	auto itr = std::find ( components [ T ].begin ( ) , components [ T ].end ( ) , component );
	if ( itr != components [ T ].end ( ) )
		components [ T ].erase ( itr );
	else
		printf ( "Proctor::Pop out of bounds exception.\n" ) ;

	component->Detach ( );
}
