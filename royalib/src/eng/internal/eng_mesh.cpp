#include "../eng_mesh.h"
#include "../eng_renderer.h"

#include "../debug/eng_dbg_renderer.h"

static Material *WhiteMaterial = NULL ;

MeshVertex::MeshVertex ( ) {
}

MeshVertex::MeshVertex ( glm::vec4 coord ) : coord ( coord ) {
}

MeshVertex::MeshVertex ( glm::vec4 coord , glm::vec3 norm ) : coord ( coord ) , norm ( norm ) {
}

MeshVertex::MeshVertex ( glm::vec4 coord , glm::vec3 norm , glm::vec2 uv ) : coord ( coord ) , norm ( norm ) , uv ( uv ) {
}

//

Mesh::Mesh ( ) : Component ( COMP_MESH ) {
	if ( WhiteMaterial == NULL ) {
		WhiteMaterial = new Material ( );
		WhiteMaterial->SetAlbedo ( glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) ) ;
	}
	material = WhiteMaterial;
	transform.SetIdentity ( ) ;
}

Mesh::Mesh ( const std::vector<MeshVertex> &vertices , const std::vector<unsigned int> &indices ) : Component ( COMP_MESH ) , vertices ( vertices ) , indices ( indices ) {
	if ( WhiteMaterial == NULL ) {
		WhiteMaterial = new Material ( );
		WhiteMaterial->SetAlbedo ( glm::vec4 ( 1.0f , 1.0f , 1.0f , 1.0f ) );
	}
	material = WhiteMaterial;
	transform.SetIdentity ( );

	aaa = glm::vec3 ( INT_MAX , INT_MAX , INT_MAX );
	bbb = glm::vec3 ( INT_MIN , INT_MIN , INT_MIN );
	for ( auto v : vertices ) {
		glm::vec3 c = v.coord;
		aaa.x = std::min ( aaa.x , c.x );
		aaa.y = std::min ( aaa.y , c.y );
		aaa.z = std::min ( aaa.z , c.z );
	}
	for ( auto v : vertices ) {
		glm::vec3 c = v.coord;
		bbb.x = std::max ( aaa.x , c.x );
		bbb.y = std::max ( aaa.y , c.y );
		bbb.z = std::max ( aaa.z , c.z );
	}
}

Mesh::~Mesh ( ) {
}

glm::vec3 Mesh::AAA ( ) const {
	glm::mat4 mat = transform.GetMatrix ( ) ;
	return mat * glm::vec4 ( aaa , 1.0f ) ;
}

glm::vec3 Mesh::BBB ( ) const {
	glm::mat4 mat = transform.GetMatrix ( );
	return mat * glm::vec4 ( bbb , 1.0f ) ;
}

void Mesh::OnInit ( ) {
	transform.SetParent ( &( ( GameObject * ) GetParent ( ) )->transform ) ;
}

void Mesh::OnUpdate ( double deltaTime ) {
	ENG_ViewportRenderer->Push ( this ) ;
#ifdef _DEBUG
	ENG_DebugRenderer->Push ( AAA ( ) , BBB ( ) , 2 ) ;
#endif
}

void Mesh::OnDestroy ( ) {
	transform.SetParent ( NULL ) ;
}
