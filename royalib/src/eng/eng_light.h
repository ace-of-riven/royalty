#pragma once

#include "eng_proctor.h"
#include "eng_component.h"
#include "eng_transform.h"

class Light : public Component {
	glm::vec3 colour;
	glm::vec3 attenuation;

	float cutOff;
	float outerCutOff;
public:
	Light ( ) ;
	Light ( const glm::vec3 &position , const glm::vec3 &colour , float intensity ) ;

	int ComponentStack ( int comp );

	void SetPointLight ( const glm::vec3& position , const glm::vec3& colour , float intensity ) ;
	void SetPointLight ( float intensity ) ;

	void SetColour ( const glm::vec3 &colour ) ;
	// alpha will be converted to itensity
	void SetColour ( const glm::vec4 &colour ) ;

	virtual void OnInit ( ) ;
	virtual void OnUpdate ( double deltaTime ) ;
	virtual void OnDestroy ( ) ;

	Transform transform;

	void SetAttenuation ( const glm::vec3 &attenuation ) ;

	inline glm::vec3 GetColour ( ) const { return colour; }
	inline glm::vec3 GetAttenuation ( ) const { return attenuation; }
	
	inline float GetCutOffAngle ( ) const { return cutOff; }
	inline float GetOuterCutOffAngle ( ) const { return outerCutOff; }
};
