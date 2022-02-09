#pragma once

#include "eng_renderer.h"

#include "eng_gameobject.h"

class StaticObject {
	unsigned int id;
	std::string name;
protected:
	std::vector<RendererBatch *> batches;
public:
	StaticObject ( ) ;
	~StaticObject ( ) ;

	void Push ( const GameObject *obj ) ;
	void Push ( const Mesh *obj ) ;

	void OnUpdate ( double deltaTime ) ;
};
