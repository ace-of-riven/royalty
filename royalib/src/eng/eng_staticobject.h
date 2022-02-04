#pragma once

#include "eng_proctor.h"
#include "eng_gameobject.h"

#include "eng_renderer.h"

#include <string>

class StaticObject : public Proctor {
	unsigned int id;
	std::string name;
protected:
	ViewportBatch *batch;
public:
	StaticObject ( const std::string &name ) ;

	int ComponentStack ( int comp );

	void Begin ( ) ;
	void Push ( const GameObject *object ) ;
	void Push ( const Mesh *mesh ) ;
	void End ( ) ;

	void OnUpdate ( double deltaTime ) ;
};
