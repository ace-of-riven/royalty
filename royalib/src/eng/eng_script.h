#pragma once

#include "eng_component.h"

class Script : public Component {
public:
	Script ( ) ;

	virtual void OnInit ( ) { }
	virtual void OnUpdate ( double deltaTime ) { }
	virtual void OnDestroy ( ) { }
};
