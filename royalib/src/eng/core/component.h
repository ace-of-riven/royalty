#pragma once

#include "../utils/enumerator.h"
#include "../utils/transform.h"

enum eComponent {
	COMP_MESH ,
	COMP_SKELETON ,
	COMP_SCRIPT ,
};

class Proctor ;

class Component {
	Proctor *owner;

	unsigned int comp_identifier;
public:
	Component ( unsigned int identifier ) ;
	virtual ~Component ( ) = default ;

	virtual void OnAttach ( ) { }
	virtual void OnUpdate ( ) { }
	virtual void OnDetach ( ) { }

	void Attach ( Proctor *owner ) ;
	void Update ( ) ;
	void Detach ( ) ;

	inline unsigned int Identifier ( ) const { return comp_identifier; }
	inline Proctor *Owner ( ) const { return owner; }
};
