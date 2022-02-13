#pragma once

#include "../renderer/renderer.h"
#include "timer.h"

static class Engine {
public:	
	static void Init ( HWND hwnd ) ;
	static void Update ( ) ;
	static void Exit ( ) ;

	static Renderer *ViewportRenderer ( ) ;
};

extern Timer EngineTimer;
