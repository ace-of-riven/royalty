#include "mesh.h"

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
}

//

Mesh *Plane ( float w , float h ) {
	static VertexData v [ 4 ] = {
	VertexData ( glm::vec4 ( -w / 2.0f ,  h / 2.0f , 0.0f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 0.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 (  w / 2.0f ,  h / 2.0f , 0.0f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 1.0f , 0.0f ) ) ,
	VertexData ( glm::vec4 (  w / 2.0f , -h / 2.0f , 0.0f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 1.0f , 1.0f ) ) ,
	VertexData ( glm::vec4 ( -w / 2.0f , -h / 2.0f , 0.0f , 1.0f ) , glm::vec3 ( 0.0f , 0.0f , -1.0f ) , glm::vec2 ( 0.0f , 1.0f ) ) };
	static IndexData i [ 6 ] = { 0 , 1 , 2 , 2 , 3 , 0 } ;
	return new Mesh ( glm::mat4 ( 1.0f ) , v , 4 , i , 6 , true ) ;
}
