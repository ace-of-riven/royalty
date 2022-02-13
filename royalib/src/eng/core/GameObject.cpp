#include "gameobject.h"

#include <map>

std::map<std::string , GameObject *> objects;

GameObject::GameObject ( GameObject *parent , const std::string &name ) : Proctor ( parent ) , name ( name ) {
	objects [ name ] = this;
}

GameObject::~GameObject ( ) {
	objects.erase ( name ) ;
}

unsigned int GameObject::ComponentStack ( unsigned int id ) const {
	switch ( id ) {
		case COMP_SCRIPT: return -1;
		case COMP_MESH: return -1;
	}
	return 0;
}

GameObject *FindGameObject ( const std::string &name ) {
	auto itr = objects.find ( name );
	if ( itr != objects.end ( ) )
		return itr->second;
	return NULL;
}
