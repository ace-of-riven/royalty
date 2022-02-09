#pragma once

#include <royalib.h>

class MainScript : public Script {
	GameObject *deset_eagle;
public:
	void OnInit ( ) ;
	void OnUpdate ( double deltaTime ) ;
};
