#pragma once

#include "timer.h"

static class Engine {
public:	
	static void Init ( ) ;
	static void Update ( ) ;
	static void Exit ( ) ;
};

extern Timer EngineTimer;
