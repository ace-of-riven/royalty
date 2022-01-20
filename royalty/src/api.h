#pragma once

#include "../resource.h"

#include "board.hpp"

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
	// sprite atlas
	std::map<std::string , Gdiplus::Image *> mAtlas;
	Gdiplus::Graphics *mGraphics;
	Gdiplus::Graphics *mBuffer;
	Gdiplus::Bitmap *mFramebuffer;
	Gdiplus::Brush *mWhite;
	Gdiplus::Brush *mBlack;
	Gdiplus::FontFamily *mFontFamily;
	Gdiplus::Font *mFont;
	Gdiplus::SolidBrush *mFontBrush;
	Gdiplus::StringFormat *mFontFormat;

	int selx , sely;
	int offx , offy;

	// active board
	ChessBoard cb;

	const int szTile = 128;
public:
	GlobalWindow ( ) ;
};
