#include "api.h"

#include "chess/config.h"

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

GlobalWindow::GlobalWindow ( ) : wl::window_main ( ) , mBoard ( ) {
	setup.size = { 720 , 720 } ;
	setup.title = L"Royalty" ;

	on_message ( WM_CREATE , [ = ] ( wl::wm::create p ) -> LRESULT {
		if ( AttachConsole ( ATTACH_PARENT_PROCESS ) || AllocConsole ( ) ) {
			freopen ( "CONOUT$" , "w" , stdout );
			freopen ( "CONOUT$" , "w" , stderr );
			freopen ( "CONIN$" , "r" , stdin );
		}
		Gdiplus::GdiplusStartupInput si;
		ULONG_PTR token;
		Gdiplus::GdiplusStartup ( &token , &si , 0 );

		// init gdi graphics
		mGraphics = new Gdiplus::Graphics ( hwnd ( ) ) ;

		// load image as bitmap, any formats supported
		mAtlas [ ID_KING | FLAG_WHITE ] = new Gdiplus::Image ( L"rc/wking.png" , false );
		mAtlas [ ID_KING | FLAG_BLACK ] = new Gdiplus::Image ( L"rc/bking.png" , false );
		mAtlas [ ID_QUEEN | FLAG_WHITE ] = new Gdiplus::Image ( L"rc/wqueen.png" , false );
		mAtlas [ ID_QUEEN | FLAG_BLACK ] = new Gdiplus::Image ( L"rc/bqueen.png" , false );
		mAtlas [ ID_BISHOP | FLAG_WHITE ] = new Gdiplus::Image ( L"rc/wbishop.png" , false );
		mAtlas [ ID_BISHOP | FLAG_BLACK ] = new Gdiplus::Image ( L"rc/bbishop.png" , false );
		mAtlas [ ID_KNIGHT | FLAG_WHITE ] = new Gdiplus::Image ( L"rc/wknight.png" , false );
		mAtlas [ ID_KNIGHT | FLAG_BLACK ] = new Gdiplus::Image ( L"rc/bknight.png" , false );
		mAtlas [ ID_ROOK | FLAG_WHITE ] = new Gdiplus::Image ( L"rc/wrook.png" , false );
		mAtlas [ ID_ROOK | FLAG_BLACK ] = new Gdiplus::Image ( L"rc/brook.png" , false );
		mAtlas [ ID_PAWN | FLAG_WHITE ] = new Gdiplus::Image ( L"rc/wpawn.png" , false );
		mAtlas [ ID_PAWN | FLAG_BLACK ] = new Gdiplus::Image ( L"rc/bpawn.png" , false );

		// create pens
		mWhite = new Gdiplus::SolidBrush ( Gdiplus::Color ( 252 , 204 , 116 ) ) ;
		mBlack = new Gdiplus::SolidBrush ( Gdiplus::Color ( 87 , 58 , 46 ) ) ;

		// font
		mFontFamily = new Gdiplus::FontFamily ( L"Times New Roman" );
		mFont = new Gdiplus::Font ( mFontFamily , 24 , Gdiplus::FontStyleRegular , Gdiplus::UnitPixel );
		mFontBrush = new Gdiplus::SolidBrush ( Gdiplus::Color ( 255 , 0 , 0 , 255 ) );
		mFontFormat = new Gdiplus::StringFormat ( ) ;
		mFontFormat->SetAlignment ( Gdiplus::StringAlignmentCenter );
		mFontFormat->SetLineAlignment ( Gdiplus::StringAlignmentCenter );

		mFramebuffer = new Gdiplus::Bitmap ( szTile * 9 , szTile * 9 );
		mBuffer = new Gdiplus::Graphics ( mFramebuffer );

		return 0;
	} );

	on_message ( WM_LBUTTONDOWN , [ = ] ( wl::wm::lbuttondown p ) -> LRESULT {
		selx = ( p.pos ( ).x * 9 ) / clientsize ( ).cx;
		sely = ( p.pos ( ).y * 9 ) / clientsize ( ).cy;
		return 0;
	} );

	on_message ( WM_MOUSEMOVE , [ = ] ( wl::wm::lbuttondown p ) -> LRESULT {
		offx = mFramebuffer->GetWidth ( ) * float ( p.pos ( ).x ) / clientsize ( ).cx;
		offy = mFramebuffer->GetHeight ( ) * float ( p.pos ( ).y ) / clientsize ( ).cy;
		return 0;
	} );

	on_message ( WM_LBUTTONUP , [ = ] ( wl::wm::lbuttonup p ) -> LRESULT {
		int tox = ( p.pos ( ).x * 9 ) / clientsize ( ).cx;
		int toy = ( p.pos ( ).y * 9 ) / clientsize ( ).cy;
		mBoard.move ( selx , sely , tox , toy );
		selx = -1;
		sely = -1;
		return 0;
	} );

	on_message ( WM_IDLE , [ = ] ( wl::params p ) -> LRESULT {
		mBuffer->Clear ( Gdiplus::Color ( 200 , 200 , 200 ) );

		for ( unsigned int y = 1; y <= 8; y++ ) {
			for ( unsigned int x = 1; x <= 8; x++ ) {
				if ( ( y * 9 + x ) % 2 )
					mBuffer->FillRectangle ( mWhite , szTile * x , szTile * y , szTile , szTile );
				else
					mBuffer->FillRectangle ( mBlack , szTile * x , szTile * y , szTile , szTile );
			}
		}
		for ( unsigned int y = 1; y <= 8; y++ ) {
			for ( unsigned int x = 1; x <= 8; x++ ) {

				if ( x == selx and y == sely ) {
				}
				else {
					unsigned char type = mBoard.piece_type ( x , y );
					unsigned char id = mBoard.piece_id ( x , y );
					Gdiplus::Image *image = mAtlas [ type | id ];
					mBuffer->DrawImage ( image , szTile * x , szTile * y , szTile , szTile );
				}
			}
		}

		// render selected pawn

		if ( 0 < selx and selx < 9 and 0 < sely and sely < 9 ) {
			unsigned char type = mBoard.piece_type ( selx , sely );
			unsigned char id = mBoard.piece_id ( selx , sely );
			Gdiplus::Image *image = mAtlas [ type | id ];
			mBuffer->DrawImage ( image , offx - szTile / 2 , offy - szTile / 2 , szTile , szTile );
		}

		for ( unsigned int y = 1; y <= 8; y++ ) {
			static wchar_t txt [ 8 ];
			swprintf_s ( txt , 8 , L"%c" , L'0' + y );
			Gdiplus::RectF rect ( 0 , szTile * y , szTile , szTile );
			mBuffer->DrawString ( txt , 1 , mFont , rect , mFontFormat , mFontBrush );
		}

		for ( unsigned int x = 1; x <= 8; x++ ) {
			static wchar_t txt [ 8 ];
			swprintf_s ( txt , 8 , L"%c" , L'@' + x );
			Gdiplus::RectF rect ( szTile * x , 0 , szTile , szTile ) ;
			mBuffer->DrawString ( txt , 1 , mFont , rect , mFontFormat , mFontBrush );
		}

		if ( mBoard.turn ( ) ) {
			static wchar_t txt [ 24 ];
			swprintf_s ( txt , 24 , L"PLAYING:\nWHITE" );
			Gdiplus::RectF rect ( 0 , 0 , szTile , szTile );
			mBuffer->DrawString ( txt , -1 , mFont , rect , mFontFormat , mFontBrush );
		}
		else {
			static wchar_t txt [ 24 ];
			swprintf_s ( txt , 24 , L"PLAYING:\nBLACK" );
			Gdiplus::RectF rect ( 0 , 0 , szTile , szTile );
			mBuffer->DrawString ( txt , -1 , mFont , rect , mFontFormat , mFontBrush );
		}

		mGraphics->DrawImage ( mFramebuffer , 0 , 0 , clientsize ( ).cx , clientsize ( ).cy ) ;

		return 0;
	} );
}

RUN ( GlobalWindow );
