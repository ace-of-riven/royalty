#include "api.h"

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

#include <thread>

#include "main/main.h"

GlobalWindow::GlobalWindow ( ) : wl::window_main ( ) {
	setup.size = { 720 , 720 } ;
	setup.style = WS_OVERLAPPEDWINDOW ;
	setup.title = L"Royalty" ;

	on_message ( WM_CREATE , [ = ] ( wl::wm::create p ) -> LRESULT {
		if ( AttachConsole ( ATTACH_PARENT_PROCESS ) || AllocConsole ( ) ) {
			freopen ( "CONOUT$" , "w" , stdout );
			freopen ( "CONOUT$" , "w" , stderr );
			freopen ( "CONIN$" , "r" , stdin );
		}

		ctx = GPU_context_create ( hwnd ( ) );
		GPU_context_active_set ( ctx );

		ROYALTY_init ( );

		dummy = new Proctor ( ) ;
		dummy->AddComponent<Script> ( new MainScript ) ;

		wglSwapIntervalEXT ( 0 ) ;
		return 0;
	} );

	on_message ( WM_DESTROY , [ = ] ( wl::wm::create p ) -> LRESULT {
		ROYALTY_exit ( );
		return 0;
	} );

	on_message ( WM_LBUTTONDOWN , [ = ] ( wl::wm::lbuttondown p ) -> LRESULT {
		return 0;
	} );

	on_message ( WM_MOUSEMOVE , [ = ] ( wl::wm::mousemove p ) -> LRESULT {
		ROYALTY_MouseUpdate ( p.pos ( ).x , p.pos ( ).y );
		return 0;
	} );

	on_message ( WM_LBUTTONUP , [ = ] ( wl::wm::lbuttonup p ) -> LRESULT {
		return 0;
	} );

	on_message ( WM_IDLE , [ = ] ( wl::params p ) -> LRESULT {
		SIZE client = clientsize ( ) ;

		GPU_context_active_set ( ctx ) ;
		glViewport ( 0 , 0 , client.cx , client.cy ) ;

		ROYALTY_update ( );

		swapbuffers ( ) ;
		return 0;
	} );
}

RUN ( GlobalWindow );
