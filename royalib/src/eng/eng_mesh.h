#pragma once

#include "../ext_include.h"

#include "eng_component.h"
#include "eng_material.h"
#include "eng_transform.h"

#include <vector>

struct MeshVertex {
	MeshVertex ( ) ;
	MeshVertex ( glm::vec4 coord ) ;
	MeshVertex ( glm::vec4 coord , glm::vec3 norm ) ;
	MeshVertex ( glm::vec4 coord , glm::vec3 norm , glm::vec2 uv );

	glm::vec4 coord;
	glm::vec3 norm;
	glm::ivec4 bone_i;
	glm::vec4 bone_w;
	glm::vec2 uv;
};

class Mesh : public Component {
	std::vector<MeshVertex> vertices;
	std::vector<unsigned int> indices;
public:
	Mesh ( ) ;
	Mesh ( const std::vector<MeshVertex>& vertices , const std::vector<unsigned int>& indices ) ;
	~Mesh ( );

	Material *material;

	Transform transform;

	void OnUpdate ( double deltaTime );

	inline const std::vector<MeshVertex> &GetVertices ( ) const { return vertices; }
	inline const std::vector<unsigned int> &GetIndices ( ) const { return indices; }
};
