#pragma once

#include "../renderer/renderer.h"
#include "../physics/physics.h"
#include "timer.h"

static class Engine {
public:	
	static void Init ( HWND hwnd ) ;
	static void Update ( ) ;
	static void Exit ( ) ;

	static Renderer *ViewportRenderer ( ) ;
	static PhysicsEngine *ViewportPhysics ( ) ;
};

extern Timer EngineTimer;
