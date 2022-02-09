#pragma once

#include "../ext_include.h"

#include "gpu_defs.h"

#define DEBUG_NAME_LEN			256

bool GPU_init ( void );
void GPU_exit ( void );
bool GPU_is_init ( void );

BOOL wglSwapIntervalEXT ( int ) ;
