#include "engine.h"

#include "../core/proctor.h"

GPU_Context *EngineContext;

Renderer *EngineViewportRenderer;
PhysicsEngine *EnginePhysics;
Timer EngineTimer;

void Engine::Init ( HWND hwnd ) {
	EngineContext = GPU_context_create ( hwnd );
	GPU_context_active_set ( EngineContext ) ;

	EngineViewportRenderer = new Renderer ( ) ;
	EnginePhysics = new PhysicsEngine ( ) ;
	EngineTimer.Reset ( ) ;
}

void Engine::Update ( ) {
	GPU_context_active_set ( EngineContext );

	EngineTimer.Update ( ) ;

	EnginePhysics->Update ( );

	EngineViewportRenderer->Begin ( ) ;
	UpdateProctors ( ) ;
	EngineViewportRenderer->Flush ( ) ;
}

void Engine::Exit ( ) {
	delete EnginePhysics;
	delete EngineViewportRenderer;
	GPU_discard_context ( EngineContext ) ;
}

Renderer *Engine::ViewportRenderer ( ) {
	return EngineViewportRenderer;
}

PhysicsEngine *Engine::ViewportPhysics ( ) {
	return EnginePhysics;
}
