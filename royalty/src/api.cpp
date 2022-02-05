#include "api.h"

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

#include <thread>

class SampleScript : public Script {
public:
	virtual void OnUpdate ( double deltaTime ) {
		GameObject *obj = ( GameObject * ) GetParent ( ) ;
		obj->transform.RotateEuler ( glm::radians ( 60.0f * deltaTime ) , 0.25f , 1.0f , 0.0f );
		// printf ( "%.1lf\n" , 1.0 / deltaTime ) ;
	}
};

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

		obj = ImportGameObject ( glm::scale ( glm::vec3 ( 1e-3f ) ) , "./rc/assets/axe/source/full.fbx" );

		obj->AddComponent<Script> ( new SampleScript ) ;

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

	on_message ( WM_MOUSEMOVE , [ = ] ( wl::wm::lbuttondown p ) -> LRESULT {
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
