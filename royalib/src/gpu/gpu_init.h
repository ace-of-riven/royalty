#pragma once

#include <windows.h>

#include "gpu_defs.h"

#include "../../ext/glew/include/gl/glew.h"

#define DEBUG_NAME_LEN			256

bool GPU_init ( void );
void GPU_exit ( void );
bool GPU_is_init ( void );

BOOL wglSwapIntervalEXT ( int ) ;
