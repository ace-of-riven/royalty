#include "main.h"

void MainScript::OnInit ( ) {
}

void MainScript::OnUpdate ( double deltaTime ) {
	ENG_DebugRenderer->Push ( glm::vec3 ( -1.0f , -0.5f , -0.5f ) , glm::vec3 ( 0.5f , 0.5f , 0.5f ) , 12 ) ;
}
