#include "mesh.h"

#include "../engine/engine.h"

VertexData::VertexData ( ) {
	this->bone_i [ 0 ] = -1;
	this->bone_i [ 1 ] = -1;
	this->bone_i [ 2 ] = -1;
	this->bone_i [ 3 ] = -1;
}

VertexData::VertexData ( const glm::vec4 &coord , const glm::vec3 &normal , const glm::vec2 &uv ) {
	this->coord = coord;
	this->norm = normal;
	this->uv = uv;

	this->bone_i [ 0 ] = -1;
	this->bone_i [ 1 ] = -1;
	this->bone_i [ 2 ] = -1;
	this->bone_i [ 3 ] = -1;
}

//

#define MESH_OWNS_BUFFERS			1

Mesh::Mesh ( ) : Component ( COMP_MESH ) {
	flag = 0;
}

Mesh::Mesh ( const Transform& transform, const std::vector<VertexData> &vertices , const std::vector<IndexData> &indices ) :
	flag ( 0 ) , transform ( transform ) , Component ( COMP_MESH ) {
	this->vertices = ( VertexData * ) malloc ( sizeof ( VertexData ) * vertices.size ( ) ) ;
	this->indices = ( IndexData * ) malloc ( sizeof ( IndexData ) * indices.size ( ) ) ;
	memcpy ( this->vertices , &vertices [ 0 ] , sizeof ( VertexData ) * vertices.size ( ) );
	memcpy ( this->indices , &indices [ 0 ] , sizeof ( IndexData ) * indices.size ( ) );
	this->vlen = vertices.size ( );
	this->ilen = indices.size ( );
	flag = MESH_OWNS_BUFFERS;
}

Mesh::Mesh ( const glm::mat4 &transform , const std::vector<VertexData> &vertices , const std::vector<IndexData> &indices ) :
	flag ( 0 ) , transform ( transform ) , Component ( COMP_MESH ) {
	this->vertices = ( VertexData * ) malloc ( sizeof ( VertexData ) * vertices.size ( ) );
	this->indices = ( IndexData * ) malloc ( sizeof ( IndexData ) * indices.size ( ) );
	memcpy ( this->vertices , &vertices [ 0 ] , sizeof ( VertexData ) * vertices.size ( ) );
	memcpy ( this->indices , &indices [ 0 ] , sizeof ( IndexData ) * indices.size ( ) );
	this->vlen = vertices.size ( );
	this->ilen = indices.size ( );
	flag = MESH_OWNS_BUFFERS;
}

// the only reasons this exist are for standard meshes shared memory so that we don't copy or store any extra data
Mesh::Mesh ( const glm::mat4 &transform , VertexData *vertices , unsigned int vlen , IndexData *indices , unsigned int ilen , bool shared ) :
	flag ( 0 ) , transform ( transform ) , Component ( COMP_MESH ) {
	this->vertices = vertices;
	this->indices = indices;
	this->vlen = vlen;
	this->ilen = ilen;
	if ( shared == false )
		flag = MESH_OWNS_BUFFERS;
}

Mesh::Mesh ( const glm::mat4 &transform , const VertexData *vertices , unsigned int vlen , const IndexData *indices , unsigned int ilen ) :
	flag ( 0 ) , transform ( transform ) , Component ( COMP_MESH ) {
	this->vertices = ( VertexData * ) malloc ( sizeof ( VertexData ) * vlen );
	this->indices = ( IndexData * ) malloc ( sizeof ( IndexData ) * ilen );
	memcpy ( this->vertices , &vertices [ 0 ] , sizeof ( VertexData ) * vlen );
	memcpy ( this->indices , &indices [ 0 ] , sizeof ( IndexData ) * ilen );
	this->vlen = vlen;
	this->ilen = ilen;
	flag = MESH_OWNS_BUFFERS;
}

Mesh::~Mesh ( ) {
	if ( flag & MESH_OWNS_BUFFERS ) {
		free ( this->vertices );
		free ( this->indices );
	}
}

bool Mesh::OwnsBuffers ( ) const {
	return flag & MESH_OWNS_BUFFERS;
}

void Mesh::OnUpdate ( ) {
	if ( Owner ( ) )
		Engine::ViewportRenderer ( )->Submit ( Owner ( )->FinalTransform ( ) , this ) ;
}

//

Mesh *Plane ( float w , float h ) {
	static VertexData v [ 4 ] = {
	VertexData ( glm::vec4 ( -0.5f ,  0.5f , 0.0f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 0.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f ,  0.5f , 0.0f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 1.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f , -0.5f , 0.0f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 1.0f , 1.0f ) ) ,
	VertexData ( glm::vec4 ( -0.5f , -0.5f , 0.0f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 0.0f , 1.0f ) ) };
	static IndexData i [ 6 ] = { 0 , 1 , 2 , 2 , 3 , 0 } ;
	return new Mesh ( glm::scale ( glm::vec3 ( w , h , 1.0f ) ) , v , 4 , i , 6 , true ) ;
}

Mesh *Cube ( float w , float h , float d ) {
	static VertexData v [ 24 ] = {
	// top
	VertexData ( glm::vec4 ( -0.5f ,  0.5f , -0.5f , 1.0f ) , glm::vec3 ( 0.0f , 1.0f , -1.0f ) , glm::vec2 ( 0.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f ,  0.5f , -0.5f , 1.0f ) , glm::vec3 ( 0.0f , 1.0f , -1.0f ) , glm::vec2 ( 1.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 ( -0.5f ,  0.5f ,  0.5f , 1.0f ) , glm::vec3 ( 0.0f , 1.0f , -1.0f ) , glm::vec2 ( 1.0f , 1.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f ,  0.5f ,  0.5f , 1.0f ) , glm::vec3 ( 0.0f , 1.0f , -1.0f ) , glm::vec2 ( 0.0f , 1.0f ) ) ,

	// bottom
	VertexData ( glm::vec4 ( -0.5f , -0.5f , -0.5f , 1.0f ) , glm::vec3 ( 0.0f , -1.0f , 0.0f ) , glm::vec2 ( 0.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f , -0.5f , -0.5f , 1.0f ) , glm::vec3 ( 0.0f , -1.0f , 0.0f ) , glm::vec2 ( 1.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 ( -0.5f , -0.5f ,  0.5f , 1.0f ) , glm::vec3 ( 0.0f , -1.0f , 0.0f ) , glm::vec2 ( 1.0f , 1.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f , -0.5f ,  0.5f , 1.0f ) , glm::vec3 ( 0.0f , -1.0f , 0.0f ) , glm::vec2 ( 0.0f , 1.0f ) ) ,

	// front
	VertexData ( glm::vec4 ( -0.5f ,  0.5f , -0.5f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 0.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f ,  0.5f , -0.5f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 1.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 ( -0.5f , -0.5f , -0.5f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 1.0f , 1.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f , -0.5f , -0.5f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 0.0f , 1.0f ) ) ,

	// back
	VertexData ( glm::vec4 ( -0.5f ,  0.5f ,  0.5f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f ,  1.0f ) , glm::vec2 ( 0.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f ,  0.5f ,  0.5f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f ,  1.0f ) , glm::vec2 ( 1.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 ( -0.5f , -0.5f ,  0.5f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f ,  1.0f ) , glm::vec2 ( 1.0f , 1.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f , -0.5f ,  0.5f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f ,  1.0f ) , glm::vec2 ( 0.0f , 1.0f ) ) ,

	// left
	VertexData ( glm::vec4 ( -0.5f ,  0.5f ,  0.5f , 1.0f ) , glm::vec3 ( -1.0f , 0.0f , 0.0f ) , glm::vec2 ( 1.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 ( -0.5f ,  0.5f , -0.5f , 1.0f ) , glm::vec3 ( -1.0f , 0.0f , 0.0f ) , glm::vec2 ( 1.0f , 1.0f ) ) ,
	VertexData ( glm::vec4 ( -0.5f , -0.5f ,  0.5f , 1.0f ) , glm::vec3 ( -1.0f , 0.0f , 0.0f ) , glm::vec2 ( 1.0f , 1.0f ) ) ,
	VertexData ( glm::vec4 ( -0.5f , -0.5f , -0.5f , 1.0f ) , glm::vec3 ( -1.0f , 0.0f , 0.0f ) , glm::vec2 ( 0.0f , 1.0f ) ) ,
	
	// right
	VertexData ( glm::vec4 (  0.5f ,  0.5f ,  0.5f , 1.0f ) , glm::vec3 (  1.0f , 0.0f , 0.0f ) , glm::vec2 ( 1.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f ,  0.5f , -0.5f , 1.0f ) , glm::vec3 (  1.0f , 0.0f , 0.0f ) , glm::vec2 ( 1.0f , 1.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f , -0.5f ,  0.5f , 1.0f ) , glm::vec3 (  1.0f , 0.0f , 0.0f ) , glm::vec2 ( 1.0f , 1.0f ) ) ,
	VertexData ( glm::vec4 (  0.5f , -0.5f , -0.5f , 1.0f ) , glm::vec3 (  1.0f , 0.0f , 0.0f ) , glm::vec2 ( 0.0f , 1.0f ) ) };
	static IndexData i [ 36 ] = {
	 0,  1,  2,  2,  3,  1,		//Top
	 4,  5,  6,  6,  7,  5,		//Bottom
	 8,  9, 10, 10, 11,  9,		//Front
	12, 13, 14, 14, 15, 13,		//Back
	16, 17, 18, 18, 19, 17,		//Left
	20, 21, 22, 22, 23, 21 }; 	//Right
	return new Mesh ( glm::scale ( glm::vec3 ( w , h , d ) ) , v , 24 , i , 36 , true );
}

Mesh *Sphere ( float radius , unsigned int rings , unsigned int sectors ) {
	const float R = 1. / ( float ) ( rings - 1 );
	const float S = 1. / ( float ) ( sectors - 1 );
	std::vector<VertexData> v;
	for ( unsigned int r = 0; r < rings; r++ ) for ( unsigned int s = 0; s < sectors; s++ ) {
		const float y = sin ( -glm::two_pi<float> ( ) + glm::pi<float> ( ) * r * R ) ;
		const float x = cos ( 2.0f * glm::pi<float> ( ) * s * S ) * sin ( glm::pi<float> ( ) * r * R );
		const float z = sin ( 2.0f * glm::pi<float> ( ) * s * S ) * sin ( glm::pi<float> ( ) * r * R );

		v.push_back ( VertexData (
			glm::vec4 ( x , y , z , 1.0f ) ,
			glm::vec3 ( x , y , z ) ,
			glm::vec2 ( s * S , r * R )
		) );
	}
	std::vector<IndexData> i;
	for ( unsigned int r = 0; r < rings; r++ ) for ( unsigned int s = 0; s < sectors; s++ ) {
		i.push_back ( r * sectors + s );
		i.push_back ( r * sectors + ( s + 1 ) );
		i.push_back ( ( r + 1 ) * sectors + ( s + 1 ) );

		i.push_back ( ( r + 1 ) * sectors + ( s + 1 ) );
		i.push_back ( ( r + 1 ) * sectors + s );
		i.push_back ( r * sectors + s );
	}
	return new Mesh ( glm::scale ( glm::vec3 ( radius , radius , radius ) ) , v , i );
}
