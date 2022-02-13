#pragma once

#include "../../ext_include.h"

class PhysicsEngine {
	reactphysics3d::PhysicsCommon physicsCommon;
	reactphysics3d::PhysicsWorld *world;
public:
	PhysicsEngine ( ) ;

	void Update ( ) ;
};
