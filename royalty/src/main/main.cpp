#include "main.h"

void MainScript::OnInit ( ) {
	deset_eagle = ImportGameObject ( glm::scale ( glm::vec3 ( 0.05f ) ) , "./rc/assets/desert_eagle/model.fbx" , false ) ;
	// deset_eagle->transform.RotateEuler ( glm::radians ( 90.0f ) , 0.0f , 1.0f , 0.0f ) ;
}

void MainScript::OnUpdate ( double deltaTime ) {
	GPU_matrix_ortho_set ( -10.0f , 10.0f , -10.0f , 10.0f , -10.0f , 10.0f ) ;
	if ( GetKeyState ( 'W' ) < 0 )
		deset_eagle->transform.RotateEuler ( glm::radians ( deltaTime * 90.0f ) , 1.0f , 0.0f , 0.0f );
	if ( GetKeyState ( 'S' ) < 0 )
		deset_eagle->transform.RotateEuler ( glm::radians ( deltaTime * 90.0f ) , -1.0f , 0.0f , 0.0f );
	if ( GetKeyState ( 'A' ) < 0 )
		deset_eagle->transform.RotateEuler ( glm::radians ( deltaTime * 90.0f ) , 0.0f , -1.0f , 0.0f );
	if ( GetKeyState ( 'D' ) < 0 )
		deset_eagle->transform.RotateEuler ( glm::radians ( deltaTime * 90.0f ) , 0.0f , 1.0f , 0.0f );
	printf ( "%d\n" , int ( 1.0 / deltaTime ) ) ;
}
