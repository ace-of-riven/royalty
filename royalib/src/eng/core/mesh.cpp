#include "mesh.h"

Mesh::Mesh ( ) : Component ( COMP_MESH ) {
}

Mesh::Mesh ( const Transform& transform, const std::vector<VertexData> &vertices , const std::vector<IndexData> &indices ) :
	transform ( transform ) , vertices ( vertices ) , indices ( indices ) , Component ( COMP_MESH ) {
}

Mesh::Mesh ( const glm::mat4 &transform , const std::vector<VertexData> &vertices , const std::vector<IndexData> &indices ) :
	transform ( transform ) , vertices ( vertices ) , indices ( indices ) , Component ( COMP_MESH ) {
}

Mesh::~Mesh ( ) {
}
