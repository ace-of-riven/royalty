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
}

Mesh::~Mesh ( ) {
}

void Mesh::OnInit ( ) {
	transform.SetParent ( &( ( GameObject * ) GetParent ( ) )->transform ) ;
}

void Mesh::OnUpdate ( double deltaTime ) {
	ENG_ViewportRenderer->Push ( this ) ;
}

void Mesh::OnDestroy ( ) {
	transform.SetParent ( NULL ) ;
}
