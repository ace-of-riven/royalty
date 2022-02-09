#include "../eng_light.h"
#include "../eng_renderer.h"

int Light::ComponentStack ( int comp ) {
	switch ( comp ) {
		case COMP_SCRIPT: return PROCTOR_MAX;
	}
	return 0;
}

Light::Light ( ) : Component ( COMP_LIGHT ) {
	colour = glm::vec3 ( 1.0f , 1.0f , 1.0f ) ;
	attenuation = glm::vec3 ( 0.0f , 1.0f , 0.0f ) ;

	cutOff = glm::radians ( 360.0f ) ;
	outerCutOff = glm::radians ( 360.0f ) ;
}

Light::Light ( const glm::vec3 &position , const glm::vec3 &colour , float intensity ) : Component ( COMP_LIGHT ) , colour ( colour * intensity ) {
	attenuation = glm::vec3 ( 0.0f , 1.0f , 0.0f );

	transform.SetIdentity ( );
	transform.Move ( position.x , position.y , position.z );

	cutOff = glm::radians ( 360.0f );
	outerCutOff = glm::radians ( 360.0f );
}

void Light::SetPointLight ( const glm::vec3 &position , const glm::vec3 &colour , float intensity ) {
	transform.SetIdentity ( );
	transform.Move ( position.x , position.y , position.z ) ;

	cutOff = glm::radians ( 360.0f );
	outerCutOff = glm::radians ( 360.0f );

	SetColour ( colour * intensity ) ;
}

void Light::SetPointLight ( float intensity ) {
	cutOff = glm::radians ( 360.0f );
	outerCutOff = glm::radians ( 360.0f );

	SetColour ( colour * intensity );
}

void Light::SetAttenuation ( const glm::vec3 &_attenuation ) {
	attenuation = _attenuation;
}

void Light::SetColour ( const glm::vec3 &_colour ) {
	colour = _colour;
}

// alpha will be converted to itensity
void Light::SetColour ( const glm::vec4 &_colour ) {
	colour = glm::vec3 ( _colour.r , _colour.g , _colour.b ) * _colour.a;
}

void Light::OnInit ( ) {
	transform.SetParent ( &GetParent ( )->transform );
}

void Light::OnUpdate ( double deltaTime ) {
	ENG_ViewportRenderer->Push ( this ) ;
}

void Light::OnDestroy ( ) {
	transform.SetParent ( NULL ) ;
}
