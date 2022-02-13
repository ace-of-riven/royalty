#include "../engine/engine.h"

#include "physics.h"

PhysicsEngine::PhysicsEngine ( ) {
	// Create the world settings 
	reactphysics3d::PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 20;
	settings.isSleepingEnabled = false;
	settings.gravity = reactphysics3d::Vector3 ( 0 , -9.81 , 0 );

	world = physicsCommon.createPhysicsWorld ( settings );
}

void PhysicsEngine::Update ( ) {
	float target = EngineTimer.deltaTime ;
	while ( target > 0.0f ) {
		float dt = std::min ( target , 1.0f / 144.0f ) ;

		world->update ( dt ) ;

		target -= dt;
	}
}
