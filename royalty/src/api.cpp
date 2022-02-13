#include "api.h"

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

#include <thread>

class IdleRotation : public Script {
public:
	void OnAttach ( ) {

	}
	void OnUpdate ( ) {
		Owner ( )->transform.Rotation += glm::vec3 ( 0.0f , EngineTimer.deltaTime * glm::radians ( 90.0f ) , 0.0f ) ;
		Owner ( )->transform.Rotation += glm::vec3 ( EngineTimer.deltaTime * glm::radians ( 90.0f ) , 0.0f , 0.0f ) ;
	}
};

GlobalWindow::GlobalWindow ( ) : wl::window_main ( ) {
	setup.size = { 1280 , 720 } ;
	setup.title = L"Royalty" ;

	GameObject *cube = new GameObject ( NULL , "cube" ) ;

	on_message ( WM_CREATE , [ = ] ( wl::wm::create p ) -> LRESULT {
		if ( AttachConsole ( ATTACH_PARENT_PROCESS ) || AllocConsole ( ) ) {
			freopen ( "CONOUT$" , "w" , stdout );
			freopen ( "CONOUT$" , "w" , stderr );
			freopen ( "CONIN$" , "r" , stdin );
		}
		Engine::Init ( hwnd ( ) ) ;

		cube->AddComponent<Mesh> ( Cube ( 0.5f , 0.5f , 0.5f ) );
		cube->AddComponent<Script> ( new IdleRotation );
		return 0;
	} );

	on_message ( WM_IDLE , [ = ] ( wl::params p ) -> LRESULT {
		Engine::Update ( ) ;

		swapbuffers ( ) ;
		return 0;
	} );
}

RUN ( GlobalWindow );
