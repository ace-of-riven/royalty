#pragma once

#include "../resource.h"

#include <map>

#include <royalib.h>

#define min(a,b)			(((a)<(b))?(a):(b))
#define max(a,b)			(((a)>(b))?(a):(b))

#include <objidl.h>
#include <gdiplus.h>

#undef min
#undef max

#pragma comment (lib,"Gdiplus.lib")

class GlobalWindow : public wl::window_main {
	GPU_Context *ctx;
	GameObject *obj;
public:
	GlobalWindow ( ) ;
};
