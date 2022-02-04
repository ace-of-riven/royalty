#include "../eng_component.h"

Component::Component ( int identifier ) : identifier ( identifier ) {
}

void Component::Attach ( Proctor *proctor ) {
	parent = proctor;
	Init ( ) ;
}

void Component::Detach ( ) {
	Destroy ( ) ;
	parent = nullptr;
}

void Component::Init ( ) {
	OnInit ( ) ;
}

void Component::Update ( double deltaTime ) {
	OnUpdate ( deltaTime ) ;
}

void Component::Destroy ( ) {
	OnDestroy ( ) ;
}
