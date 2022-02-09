#pragma once

#include "../resource.h"

#include <map>

#include <royalib.h>

class GlobalWindow : public wl::window_main {
	GPU_Context *ctx;
	Proctor *dummy;
public:
	GlobalWindow ( ) ;
};
