#include "api.h"

#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>

#include <thread>

class SampleScript : public Script {
public:
	virtual void OnUpdate ( double deltaTime ) {
		float dt ( deltaTime ) ;
		GetParent ( )->GetComponent<Mesh> ( )->transform *= glm::rotate ( glm::radians ( 180.0f ) * dt , glm::vec3 ( 0.0f , 0.0f , 1.0f ) ) ;
		GetParent ( )->GetComponent<Mesh> ( )->transform *= glm::rotate ( glm::radians ( 180.0f ) * dt , glm::vec3 ( 0.0f , 1.0f , 0.0f ) ) ;
	}
};

GlobalWindow::GlobalWindow ( ) : wl::window_main ( ) {
	setup.size = { 1280 , 720 } ;
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

		GameObject *obj = new GameObject ( "test" ) ;

		std::vector<MeshVertex> vertices ;
		vertices.push_back ( MeshVertex ( glm::vec4 ( -0.5f ,  0.5f , 0.0f , 1.0f ) , glm::vec3 ( ) , glm::vec2 ( 0.0f , 0.0f ) ) ) ;
		vertices.push_back ( MeshVertex ( glm::vec4 (  0.5f ,  0.5f , 0.0f , 1.0f ) , glm::vec3 ( ) , glm::vec2 ( 1.0f , 0.0f ) ) ) ;
		vertices.push_back ( MeshVertex ( glm::vec4 (  0.5f , -0.5f , 0.0f , 1.0f ) , glm::vec3 ( ) , glm::vec2 ( 1.0f , 1.0f ) ) ) ;
		vertices.push_back ( MeshVertex ( glm::vec4 ( -0.5f , -0.5f , 0.0f , 1.0f ) , glm::vec3 ( ) , glm::vec2 ( 0.0f , 1.0f ) ) ) ;

		std::vector<unsigned int> indices;
		indices.push_back ( 0 ); indices.push_back ( 1 ); indices.push_back ( 2 );
		indices.push_back ( 2 ); indices.push_back ( 3 ); indices.push_back ( 0 );

		Mesh *mesh = new Mesh ( vertices , indices );

		mesh->material = new Material ( );
		mesh->material->SetAlbedo ( glm::vec4 ( 1.0f , 0.5f , 0.0f , 1.0f ) );

		obj->AddComponent<Mesh> ( mesh ) ;

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
