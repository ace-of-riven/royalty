#include "../eng_transform.h"

Transform::Transform ( ) {
	scalation = glm::vec3 ( 1.0f , 1.0f , 1.0f ) ;
	rotation = glm::vec3 ( 0.0f , 0.0f , 0.0f ) ;
	position = glm::vec3 ( 0.0f , 0.0f , 0.0f ) ;
	parent = NULL;
}

Transform::~Transform ( ) {
}

void Transform::FromMatrix ( const glm::mat4 &matrix ) {
	glm::quat _rotation;
	glm::vec3 _skew;
	glm::vec4 _perspective;
	glm::decompose ( matrix , scalation , _rotation , position , _skew , _perspective );

	// YXZ
	glm::vec3 euler = glm::eulerAngles ( _rotation ) * 3.14159f / 180.f;

	rotation = glm::vec3 ( euler [ 1 ] , euler [ 0 ] , euler [ 2 ] ) ;
}

void Transform::SetParent ( Transform *transform ) {
	parent = transform;
}

void Transform::SetIdentity ( ) {
	scalation = glm::vec3 ( 1.0f , 1.0f , 1.0f );
	rotation = glm::vec3 ( 0.0f , 0.0f , 0.0f );
	position = glm::vec3 ( 0.0f , 0.0f , 0.0f );
}

void Transform::RotateEuler ( float Angle , float X , float Y , float Z ) {
	rotation += Angle * glm::vec3 ( X , Y , Z );
}

void Transform::Move ( float X , float Y , float Z ) {
	position += glm::vec3 ( X , Y , Z );
}

void Transform::Scale ( float X , float Y , float Z ) {
	scalation *= glm::vec3 ( X , Y , Z );
}

glm::vec3 Transform::GetLocation ( ) const {
	return glm::vec3 ( GetMatrix ( ) * glm::vec4 ( 0.0f , 0.0f , 0.0f , 1.0f ) ) ;
}

Transform Transform::operator * ( const Transform &transform ) const {
	Transform result;
	result.rotation = ( this->rotation + transform.rotation );
	result.position = ( this->position + transform.position );
	result.scalation = ( this->scalation * transform.scalation );
	return result;
}

Transform &Transform::operator = ( const Transform &transform ) {
	rotation = ( transform.rotation );
	position = ( transform.position );
	scalation = ( transform.scalation );
	return *this;
}

Transform &Transform::operator *= ( const Transform &transform ) {
	rotation = ( this->rotation + transform.rotation );
	position = ( this->position + transform.position );
	scalation = ( this->scalation * transform.scalation );
	return *this;
}

glm::mat4 Transform::GetMatrix ( ) const {
	if ( parent )
		return parent->GetMatrix ( ) * GetLocalMatrix ( );
	return GetLocalMatrix ( );
}

glm::mat4 Transform::GetLocalMatrix ( ) const {
	return glm::translate ( position ) * glm::eulerAngleXYZ ( this->rotation.x , this->rotation.y , this->rotation.z ) * glm::scale ( scalation );
}
