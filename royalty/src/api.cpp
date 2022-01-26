#include "api.h"

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

#include <thread>

GlobalWindow::GlobalWindow ( ) : wl::window_main ( ) {
	setup.size = { 1280 , 720 } ;
	setup.title = L"Royalty" ;

	on_message ( WM_CREATE , [ = ] ( wl::wm::create p ) -> LRESULT {
		if ( AttachConsole ( ATTACH_PARENT_PROCESS ) || AllocConsole ( ) ) {
			freopen ( "CONOUT$" , "w" , stdout );
			freopen ( "CONOUT$" , "w" , stderr );
			freopen ( "CONIN$" , "r" , stdin );
		}
		return 0;
	} );

	on_message ( WM_LBUTTONDOWN , [ = ] ( wl::wm::lbuttondown p ) -> LRESULT {
		return 0;
	} );

	on_message ( WM_MOUSEMOVE , [ = ] ( wl::wm::lbuttondown p ) -> LRESULT {
		return 0;
	} );

	on_message ( WM_LBUTTONUP , [ = ] ( wl::wm::lbuttonup p ) -> LRESULT {
		return 0;
	} );

	on_message ( WM_IDLE , [ = ] ( wl::params p ) -> LRESULT {
		return 0;
	} );
}

RUN ( GlobalWindow );
