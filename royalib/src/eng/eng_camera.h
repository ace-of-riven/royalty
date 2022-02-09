#pragma once

#include "../gpu/gpu_state.h"
#include "../gpu/gpu_matrix.h"

#include "eng_proctor.h"
#include "eng_transform.h"

class Camera : public Proctor {
	float m_fov;
public:
	Camera ( );

	int ComponentStack ( int comp );

	Transform transform;

	void OnUpdate ( double deltaTime );

	void SetFOV ( float fov );

	inline float GetFOV ( ) const { return m_fov; }

	glm::vec3 Front ( ) const;
	glm::vec3 Right ( ) const;
	glm::vec3 Up ( ) const;
};
