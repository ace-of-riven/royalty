#pragma once

#include "component.h"

class Script : public Component {
public:
	Script ( ) ;

	virtual void OnAttach ( ) { }
	virtual void OnUpdate ( ) { }
	virtual void OnDetach ( ) { }
};
