#include "api.h"

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

#include <thread>

class SampleScript : public Script {
public:
	virtual void OnUpdate ( double deltaTime ) {
		float dt = deltaTime ;
		GameObject *obj = ( GameObject * ) GetParent ( ) ;
		obj->transform.RotateEuler ( glm::radians ( 60.0f * dt ) , 0.25f , 1.0f , 0.0f );
		printf ( "%.1f\n" , 1.0f / dt ) ;
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

		obj = ImportObject ( "./rc/assets/cube.fbx" );
		obj->transform.Scale ( 0.25f , 0.25f , 0.25f ) ;
		obj->AddComponent<Script> ( new SampleScript ( ) ) ;

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

		glPolygonMode ( GL_FRONT_AND_BACK , GL_LINE );

		ROYALTY_update ( );

		swapbuffers ( ) ;
		return 0;
	} );
}

RUN ( GlobalWindow );
