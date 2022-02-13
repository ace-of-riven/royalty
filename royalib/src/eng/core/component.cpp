#include "component.h"
#include "proctor.h"

Component::Component ( unsigned int id ) : comp_identifier ( id ) {
}

void Component::Attach ( Proctor *owner ) {
	this->owner = owner;
	OnAttach ( ) ;
}

void Component::Update ( ) {
	OnUpdate ( ) ;
}

void Component::Detach ( ) {
	OnDetach ( ) ;
	this->owner = NULL;
}
