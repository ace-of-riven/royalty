#pragma once

#include "component.h"

#include <vector>

typedef unsigned int IndexData;

struct VertexData {
	VertexData ( ) ;
	VertexData ( const glm::vec4& coord , const glm::vec3& normal , const glm::vec2& uv ) ;

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
	IndexData *indices;
	VertexData *vertices;

	unsigned int vlen;
	unsigned int ilen;

	char flag;
public:
	Mesh ( ) ;
	Mesh ( const Transform &transform, const std::vector<VertexData>& vertices , const std::vector<IndexData>& indices ) ;
	Mesh ( const glm::mat4 &transform, const std::vector<VertexData>& vertices , const std::vector<IndexData>& indices ) ;

	Mesh ( const glm::mat4 &transform, const VertexData *vertices , unsigned int vlen , const IndexData *indices , unsigned int ilen );

	Mesh ( const glm::mat4 &transform, VertexData *vertices , unsigned int vlen , IndexData *indices , unsigned int ilen , bool shared = false ) ;
	~Mesh ( ) ;

	virtual void OnUpdate ( ) ;

	Transform transform;

	bool OwnsBuffers ( ) const ;

	inline const IndexData *Indices ( ) const { return indices; }
	inline const VertexData *Vertices ( ) const { return vertices; }
	inline unsigned int IndicesLen ( ) const { return ilen; }
	inline unsigned int VerticesLen ( ) const { return vlen; }
};

Mesh *Plane ( float width , float height ) ;
