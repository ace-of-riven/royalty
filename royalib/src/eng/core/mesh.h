#pragma once

#include "component.h"

#include <vector>

typedef unsigned int IndexData;

struct VertexData {
	glm::vec<4,float,glm::defaultp> coord ;
	glm::vec<3,float,glm::defaultp> norm ;
	glm::vec<2,float,glm::defaultp> uv ;
	glm::vec<4,float,glm::defaultp> bone_w;
	glm::vec<4,int,glm::defaultp>   bone_i;

	inline void AddBone ( int bone_idx , float wheight ) {
		unsigned int i = 0;
		while ( bone_i [ i ] != -1 and i < 4 ) i++;
		if ( i == 4 )
			return ;
		bone_i [ i ] = bone_idx;
		bone_w [ i ] = wheight;
	}
};

class Mesh : public Component {
	std::vector<IndexData> indices;
	std::vector<VertexData> vertices;
public:
	Mesh ( ) ;
	Mesh ( const Transform &transform, const std::vector<VertexData>& vertices , const std::vector<IndexData>& indices ) ;
	Mesh ( const glm::mat4 &transform, const std::vector<VertexData>& vertices , const std::vector<IndexData>& indices ) ;
	~Mesh ( ) ;

	Transform transform;

	inline const std::vector<IndexData>& Indices ( ) const { return indices; }
	inline const std::vector<VertexData>& Vertices ( ) const { return vertices; }
};
