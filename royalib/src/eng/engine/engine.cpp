#include "engine.h"

#include "../core/proctor.h"

Timer EngineTimer;

void Engine::Init ( ) {
	EngineTimer.Reset ( ) ;
}

void Engine::Update ( ) {
	EngineTimer.Update ( ) ;
	UpdateProctors ( ) ;
}

void Engine::Exit ( ) {

}
