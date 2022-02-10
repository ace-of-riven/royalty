#include "main.h"

Camera *SCENE_Camera;

void MainScript::OnInit ( ) {
	SCENE_Camera = new Camera ( ) ;
	SCENE_Camera->transform.Move ( 0.0f , 0.0f , -20.0f ) ;
	SCENE_Camera->AddComponent<Light> ( new Light ( glm::vec3 ( 0.0f , 8.0f , 0.0f ) , glm::vec3 ( 1.0f , 1.0f , 1.0f ) , 128.0f ) ) ;

	deset_eagle = ImportGameObject ( glm::scale ( glm::vec3 ( 0.05f ) ) , "./rc/assets/desert_eagle/model.fbx" , false ) ;
	deset_eagle->transform.RotateEuler ( glm::radians ( 90.0f ) , -1.0f , 0.0f , 0.0f );
	deset_eagle->transform.RotateEuler ( glm::radians ( 90.0f ) , 0.0f , 0.0f , -1.0f );
	deset_eagle->transform.Move ( -8.0f , -2.0f , 12.0f );
	
	deset_eagle->transform.SetParent ( &SCENE_Camera->transform ) ;
}

void MainScript::OnUpdate ( double deltaTime ) {
	// printf ( "%d\n" , int ( 1.0 / deltaTime ) ) ;
}
