#include "api.h"

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

#include <thread>

vector<string> prev_moves;

inline std::string location_to_str ( int x , int y ) {
	return std::string ( { char ( 'a' + y - 1 ) , char ( '8' - x + 1 ) } );
}

inline std::string move_to_str ( int fx , int fy , int tx , int ty ) {
	return location_to_str ( fx , fy ) + location_to_str ( tx , ty ) ;
}

// ========== Initializes the materials for the game ==========
void init_materials ( map<char , int> &m ) {
	// Black's Pieces
	m.insert ( pair<char , int> ( 'p' , 8 ) );
	m.insert ( pair<char , int> ( 'r' , 2 ) );
	m.insert ( pair<char , int> ( 'n' , 2 ) );
	m.insert ( pair<char , int> ( 'b' , 2 ) );
	m.insert ( pair<char , int> ( 'q' , 1 ) );
	m.insert ( pair<char , int> ( 'k' , 1 ) );

	// White's Pieces
	m.insert ( pair<char , int> ( 'P' , 8 ) );
	m.insert ( pair<char , int> ( 'R' , 2 ) );
	m.insert ( pair<char , int> ( 'N' , 2 ) );
	m.insert ( pair<char , int> ( 'B' , 2 ) );
	m.insert ( pair<char , int> ( 'Q' , 1 ) );
	m.insert ( pair<char , int> ( 'K' , 1 ) );
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
		mAtlas [ 'K' ] = new Gdiplus::Image ( L"rc/wking.png" , false );
		mAtlas [ 'k' ] = new Gdiplus::Image ( L"rc/bking.png" , false );
		mAtlas [ 'Q' ] = new Gdiplus::Image ( L"rc/wqueen.png" , false );
		mAtlas [ 'q' ] = new Gdiplus::Image ( L"rc/bqueen.png" , false );
		mAtlas [ 'B' ] = new Gdiplus::Image ( L"rc/wbishop.png" , false );
		mAtlas [ 'b' ] = new Gdiplus::Image ( L"rc/bbishop.png" , false );
		mAtlas [ 'N' ] = new Gdiplus::Image ( L"rc/wknight.png" , false );
		mAtlas [ 'n' ] = new Gdiplus::Image ( L"rc/bknight.png" , false );
		mAtlas [ 'R' ] = new Gdiplus::Image ( L"rc/wrook.png" , false );
		mAtlas [ 'r' ] = new Gdiplus::Image ( L"rc/brook.png" , false );
		mAtlas [ 'P' ] = new Gdiplus::Image ( L"rc/wpawn.png" , false );
		mAtlas [ 'p' ] = new Gdiplus::Image ( L"rc/bpawn.png" , false );

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

		root = new tNode;
		init_materials ( root->materials );
		root->cur_side = 0; // 0 denotes human/player side
		black_turn = false;

		allowed_moves ( root , 0 );

		return 0;
	} );

	on_message ( WM_LBUTTONDOWN , [ = ] ( wl::wm::lbuttondown p ) -> LRESULT {
		selx = ( p.pos ( ).x * 9 ) / clientsize ( ).cx;
		sely = ( p.pos ( ).y * 9 ) / clientsize ( ).cy;
		if ( root->cur_side != 0 )
			selx = sely = -1;
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
		if ( selx == -1 or sely == -1 )
			return 0;

		printf ( "exec : %s\n" , move_to_str ( selx , sely , tox , toy ).c_str ( ) ) ;

		if ( exec_player_move ( root , move_to_str ( selx , sely , tox , toy ) ) ) {
			black_turn = true;
		}
		else {
			printf ( "move failed.\n" ) ;
		}

		selx = -1;
		sely = -1;
		return 0;
	} );

	on_message ( WM_IDLE , [ = ] ( wl::params p ) -> LRESULT {
		mBuffer->Clear ( Gdiplus::Color ( 204 , 252 , 116 ) );

		for ( unsigned int y = 1; y <= 8; y++ ) {
			for ( unsigned int x = 1; x <= 8; x++ ) {
				if ( ( y * 9 + x ) % 2 )
					mBuffer->FillRectangle ( mWhite , szTile * x , szTile * y , szTile , szTile );
				else
					mBuffer->FillRectangle ( mBlack , szTile * x , szTile * y , szTile , szTile );
			}
		}
		for ( int i = 2; i < 10; i++ ) {
			for ( int j = 2; j < 10; j++ ) {
				Gdiplus::Image *image = mAtlas [ root->board [ i ][ j ] ];
				if ( selx != i - 1 or sely != j - 1 )
					mBuffer->DrawImage ( image , szTile * ( i - 1 ) , szTile * ( j - 1 ) , szTile , szTile );
			}
		}

		for ( char i = 'A'; i <= 'H'; i++ ) {
			unsigned int y = ( i - 'A' ) + 1;
			Gdiplus::RectF rect ( 0 , szTile * y , szTile , szTile );
			mBuffer->DrawString ( wstring ( { ( wchar_t ) i } ).c_str ( ) , -1 , mFont , rect , mFontFormat , mFontBrush ) ;
		}

		for ( char j = '8'; j >= '1'; j-- ) {
			unsigned int x = ( '8' - j ) + 1;
			Gdiplus::RectF rect ( szTile * x , 0 , szTile , szTile );
			mBuffer->DrawString ( wstring ( { ( wchar_t ) j } ).c_str ( ) , -1 , mFont , rect , mFontFormat , mFontBrush );
		}

		if ( 0 < selx and selx < 9 and 0 < sely and sely < 9 ) {
			char piece = root->board [ selx + 1 ][ sely + 1 ];
			if ( piece ) {
				Gdiplus::Image *image = mAtlas [ piece ];
				mBuffer->DrawImage ( image , offx - szTile / 2 , offy - szTile / 2 , szTile , szTile );
			}
		}

		mGraphics->DrawImage ( mFramebuffer , 0 , 0 , clientsize ( ).cx , clientsize ( ).cy ) ;

		if ( black_turn ) {
			// clear white's moves
			tree_delete ( root );
			prev_moves.clear ( );

			next_move ( root , 0 );

			minimax_alpha_beta ( root , best , 0 , 0 , LOWEST_SCORE , HIGHEST_SCORE );

			static_evals = 0;

			int a , b;
			for ( a = 0; a < 12; a++ ) {
				for ( b = 0; b < 12; b++ ) {
					root->board [ a ][ b ] = best->board [ a ][ b ];
				}
			}
			root->materials = best->materials;
			root->w_king_pos = best->w_king_pos;
			root->b_king_pos = best->b_king_pos;

			tree_delete ( root );
			prev_moves.clear ( );
			
			// get white's moves

			allowed_moves ( root , 0 );

			black_turn = false;
		}

		return 0;
	} );
}

RUN ( GlobalWindow );
