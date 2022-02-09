#include "../eng_gameobject.h"

static unsigned int gameobject_ids = 0x12;

int GameObject::ComponentStack ( int comp ) {
	switch ( comp ) {
		case COMP_SCRIPT: return PROCTOR_MAX;
		case COMP_MESH: return PROCTOR_MAX;
		case COMP_LIGHT: return PROCTOR_MAX;
	}
	return 0;
}

GameObject::GameObject ( const std::string &name ) : id ( gameobject_ids++ ) , name ( name ) {
}
