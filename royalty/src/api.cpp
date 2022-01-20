#include "api.h"

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

inline std::string location_to_str ( int x , int y ) {
	return std::string ( { char ( ChessInfo::MIN_FILE + x - 1 ) , char ( ChessInfo::MIN_RANK + y - 1 ) } );
}

GlobalWindow::GlobalWindow ( ) : wl::window_main ( ) {
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
		mAtlas [ "White's King" ] = new Gdiplus::Image ( L"rc/wking.png" , false );
		mAtlas [ "Black's King" ] = new Gdiplus::Image ( L"rc/bking.png" , false );
		mAtlas [ "White's Queen" ] = new Gdiplus::Image ( L"rc/wqueen.png" , false );
		mAtlas [ "Black's Queen" ] = new Gdiplus::Image ( L"rc/bqueen.png" , false );
		mAtlas [ "White's Bishop" ] = new Gdiplus::Image ( L"rc/wbishop.png" , false );
		mAtlas [ "Black's Bishop" ] = new Gdiplus::Image ( L"rc/bbishop.png" , false );
		mAtlas [ "White's Knight" ] = new Gdiplus::Image ( L"rc/wknight.png" , false );
		mAtlas [ "Black's Knight" ] = new Gdiplus::Image ( L"rc/bknight.png" , false );
		mAtlas [ "White's Rook" ] = new Gdiplus::Image ( L"rc/wrook.png" , false );
		mAtlas [ "Black's Rook" ] = new Gdiplus::Image ( L"rc/brook.png" , false );
		mAtlas [ "White's Pawn" ] = new Gdiplus::Image ( L"rc/wpawn.png" , false );
		mAtlas [ "Black's Pawn" ] = new Gdiplus::Image ( L"rc/bpawn.png" , false );

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

		cb.resetBoard ( ) ;

		return 0;
	} );

	on_message ( WM_LBUTTONDOWN , [ = ] ( wl::wm::lbuttondown p ) -> LRESULT {
		selx = ( p.pos ( ).x * 9 ) / clientsize ( ).cx;
		sely = ( p.pos ( ).y * 9 ) / clientsize ( ).cy;
		Piece *piece = cb.at ( location_to_str ( selx , sely ) ) ;
		if ( piece == NULL or piece->isWhitePlayer ( ) != cb.whiteTurn ( ) ) {
			selx = -1;
			sely = -1;
		}
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
		cb.submitMove ( location_to_str ( selx , sely ).c_str ( ) ,
				location_to_str ( tox , toy ).c_str ( ) ) ;
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
		for ( char i = ChessInfo::MAX_RANK; i >= ChessInfo::MIN_RANK; i-- ) {
			for ( char j = ChessInfo::MIN_FILE; j <= ChessInfo::MAX_FILE; j++ ) {
				Piece *piece = cb.at ( i , j );
				if ( piece ) {
					Gdiplus::Image *image = mAtlas [ piece->toString ( ) ];
					unsigned int x = ( j - ChessInfo::MIN_FILE ) + 1;
					unsigned int y = ( i - ChessInfo::MIN_RANK ) + 1;
					if ( x != selx or y != sely )
						mBuffer->DrawImage ( image , szTile * x , szTile * y , szTile , szTile );
				}
			}
		}

		for ( char i = ChessInfo::MAX_RANK; i >= ChessInfo::MIN_RANK; i-- ) {
			unsigned int y = ( i - ChessInfo::MIN_RANK ) + 1;
			Gdiplus::RectF rect ( 0 , szTile * y , szTile , szTile );
			mBuffer->DrawString ( wstring ( { ( wchar_t ) i } ).c_str ( ) , -1 , mFont , rect , mFontFormat , mFontBrush ) ;
		}

		for ( char j = ChessInfo::MIN_FILE; j <= ChessInfo::MAX_FILE; j++ ) {
			unsigned int x = ( j - ChessInfo::MIN_FILE ) + 1;
			Gdiplus::RectF rect ( szTile * x , 0 , szTile , szTile );
			mBuffer->DrawString ( wstring ( { ( wchar_t ) j } ).c_str ( ) , -1 , mFont , rect , mFontFormat , mFontBrush );
		}

		if ( 0 < selx and selx < 9 and 0 < sely and sely < 9 ) {
			Piece *piece = cb.at ( location_to_str ( selx , sely ) ) ;
			if ( piece ) {
				Gdiplus::Image *image = mAtlas [ piece->toString ( ) ];
				mBuffer->DrawImage ( image , offx - szTile / 2 , offy - szTile / 2 , szTile , szTile );
			}
		}

		if ( cb.whiteTurn ( ) ) {
			static wchar_t txt [ 24 ];
			swprintf_s ( txt , 24 , L"WHITE" );
			Gdiplus::RectF rect ( 0 , 0 , szTile , szTile );
			mBuffer->DrawString ( txt , -1 , mFont , rect , mFontFormat , mFontBrush );
		}
		else {
			static wchar_t txt [ 24 ];
			swprintf_s ( txt , 24 , L"BLACK" );
			Gdiplus::RectF rect ( 0 , 0 , szTile , szTile );
			mBuffer->DrawString ( txt , -1 , mFont , rect , mFontFormat , mFontBrush );
		}

		mGraphics->DrawImage ( mFramebuffer , 0 , 0 , clientsize ( ).cx , clientsize ( ).cy ) ;

		return 0;
	} );
}

RUN ( GlobalWindow );
