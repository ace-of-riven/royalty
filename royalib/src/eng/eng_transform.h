#pragma once

#include "../ext_include.h"

class Transform {
	Transform *parent;
protected:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scalation;
public:
	Transform ( ) ;
	~Transform ( ) ;

	void SetParent ( Transform *transform ) ;
	void SetIdentity ( ) ;

	void RotateEuler ( float Angle , float X , float Y , float Z ) ;
	void Move ( float X , float Y , float Z ) ;
	void Scale ( float X , float Y , float Z ) ;

	Transform operator * ( const Transform &transform ) const ;
	Transform &operator = ( const Transform &transform );
	Transform &operator *= ( const Transform &transform );

	glm::mat4 GetMatrix ( ) const ;
	glm::mat4 GetLocalMatrix ( ) const ;
};