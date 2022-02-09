#pragma once

#include <royalib.h>

class MainScript : public Script {
	GameObject *player;
public:
	void OnInit ( ) ;
	void OnUpdate ( double deltaTime ) ;
};
