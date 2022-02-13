#include "api.h"

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

#include <thread>

GlobalWindow::GlobalWindow ( ) : wl::window_main ( ) {
	setup.size = { 1280 , 720 } ;
	setup.title = L"Royalty" ;

	Proctor *test = new Proctor ( ) ;

	on_message ( WM_CREATE , [ = ] ( wl::wm::create p ) -> LRESULT {
		if ( AttachConsole ( ATTACH_PARENT_PROCESS ) || AllocConsole ( ) ) {
			freopen ( "CONOUT$" , "w" , stdout );
			freopen ( "CONOUT$" , "w" , stderr );
			freopen ( "CONIN$" , "r" , stdin );
		}
		Engine::Init ( hwnd ( ) ) ;
		return 0;
	} );

	on_message ( WM_IDLE , [ = ] ( wl::params p ) -> LRESULT {
		Engine::Update ( ) ;

		swapbuffers ( ) ;
		return 0;
	} );
}

RUN ( GlobalWindow );
