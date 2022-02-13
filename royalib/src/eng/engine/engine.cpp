#include "engine.h"

#include "../core/proctor.h"

GPU_Context *EngineContext;

Renderer *EngineViewportRenderer;
Timer EngineTimer;

void Engine::Init ( HWND hwnd ) {
	EngineContext = GPU_context_create ( hwnd );
	GPU_context_active_set ( EngineContext ) ;

	EngineViewportRenderer = new Renderer ( ) ;
	EngineTimer.Reset ( ) ;
}

void Engine::Update ( ) {
	GPU_context_active_set ( EngineContext );

	EngineTimer.Update ( ) ;
	EngineViewportRenderer->Begin ( ) ;
	UpdateProctors ( ) ;
	EngineViewportRenderer->Flush ( ) ;
}

void Engine::Exit ( ) {
	delete EngineViewportRenderer;
	GPU_discard_context ( EngineContext ) ;
}

Renderer *Engine::ViewportRenderer ( ) {
	return EngineViewportRenderer;
}
