#pragma once

class Proctor;

class Component {
	int identifier;
	Proctor *parent;
public:
	Component ( int identifier ) ;

	inline Proctor *GetParent ( ) const { return parent; }
	inline int Identifier ( ) const { return identifier; }

	virtual void OnInit ( ) { }
	virtual void OnUpdate ( double deltaTime ) { }
	virtual void OnDestroy ( ) { }

	void Attach ( Proctor *proctor ) ;
	void Detach ( ) ;

	void Init ( );
	void Update ( double deltaTime );
	void Destroy ( );
};

enum COMPONENT_IDENTIFIER {
	COMP_INVALID = -1 ,
	COMP_SCRIPT = 1 ,
	COMP_MESH ,
};
