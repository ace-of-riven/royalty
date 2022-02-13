#pragma once

#include "../../ext_include.h"

struct Transform {
	Transform ( ) = default ;
	Transform ( const glm::mat4 &matrix ) ;
	~Transform ( ) = default ;

	glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

	glm::mat4 GetTransform ( ) const;
};
