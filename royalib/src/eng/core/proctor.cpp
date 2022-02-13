#include "proctor.h"

#include <set>
#include <algorithm>

std::set<Proctor *> Proctors;

unsigned int Proctor::ComponentStack ( unsigned int id ) const {
	switch ( id ) {
		case COMP_SCRIPT: return -1;
	}
	return 0;
}

Proctor::Proctor ( ) : is_initialized ( false ) {
	Proctors.insert ( this ) ;
}

Proctor::~Proctor ( ) {
	Proctors.erase ( this ) ;
}

void Proctor::Update ( ) {
	if ( is_initialized == false ) {
		OnInit ( ) ;
		is_initialized = true ;
	}

	// update components
	for ( auto& comp_list : components ) {
		for ( auto &comp : comp_list.second ) {
			comp->Update ( ) ;
		}
	}

	OnUpdate ( ) ;
}

void UpdateProctors ( ) {
	for ( auto proctor : Proctors ) {
		proctor->Update ( ) ;
	}
}