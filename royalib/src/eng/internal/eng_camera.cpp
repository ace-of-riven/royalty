#include "../eng_camera.h"

Camera::Camera ( ) : m_fov ( 60.0f ) {
}

int Camera::ComponentStack ( int m_type ) {
	switch ( m_type ) {
		case COMP_SCRIPT: return PROCTOR_MAX;
		case COMP_LIGHT: return PROCTOR_MAX;
	}
	return 0;
}

void Camera::SetFOV ( float fov ) {
	m_fov = fov;
}

void Camera::OnUpdate ( double deltaTime ) {
	glm::vec3 m_pos = transform.Position ( );
	glm::vec3 m_rot = transform.Rotation ( );
	float viewport [ 4 ];
	GPU_viewport_size_get_f ( viewport ) ;
	glm::mat4 proj_mat = glm::perspective ( glm::radians ( m_fov ) , viewport [ 2 ] / viewport [ 3 ] , 1e-1f , 1e4f ) ;
	glm::mat4 vtrn_mat = glm::translate ( glm::mat4 ( 1 ) , { -m_pos.x,-m_pos.y,-m_pos.z } );
	glm::mat4 vrot_mat = glm::rotate ( glm::rotate ( glm::mat4 ( 1 ) , m_rot.x , { 1, 0, 0 } ) , m_rot.y + glm::radians ( 180.0f ) , { 0, 1, 0 } );

	GPU_matrix_projection_set ( proj_mat * vrot_mat * vtrn_mat );
}

glm::vec3 Camera::Front ( ) const {
	glm::vec3 m_rot = transform.Rotation ( );
	return glm::normalize ( glm::vec3 ( -sin ( m_rot.y ) , sin ( m_rot.x ) , cos ( m_rot.y ) ) );
}

glm::vec3 Camera::Right ( ) const {
	glm::vec3 m_rot = transform.Rotation ( );
	return glm::normalize ( glm::vec3 ( cos ( m_rot.y ) , 0.0f , sin ( m_rot.y ) ) );
}

glm::vec3 Camera::Up ( ) const {
	return glm::vec3 ( );
}
