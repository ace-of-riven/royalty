out vec4 FragColor;

layout(std140, binding = 0) uniform MaterialProperties {
	struct {
		vec4 AlbedoC ;
		int AlbedoT ;
	} Material [ MAX_MATERIALS ] ;
};

layout(std140, binding = 2) uniform LightProperties {
	int LightCount;
	struct {
		vec3 Location;
		vec3 Colour;
		vec3 Attenuation;
		vec3 Direction;
		float cutOff;
		float outerCutOff;
	} Lights [ MAX_LIGHTS ] ;
};

uniform sampler2D uTexture [ MAX_FRAG_TEXTURES ] ;

in vec2 uv;
in vec3 norm;
in vec3 pos;

flat in int MatID ;

vec3 ComputeLight ( int off , vec3 colour ) {
	vec3 lightDir = normalize ( Lights [ off ].Location - pos );
	float theta = dot ( lightDir , normalize ( -Lights [ off ].Direction ) ) ;
	// remember that we're working with angles as cosines instead of degrees so a '>' is used.
	if(theta < Lights [ off ].cutOff)
	{
		float dist = length ( Lights [ off ].Location - pos ) ;
		float mul = 1.0 / ( Lights [ off ].Attenuation.x * dist +Lights [ off ].Attenuation.y * dist * dist + Lights [ off ].Attenuation.z * dist * dist * dist ) ;
		
		vec3 N = normalize(norm);
        float diff = max(dot(norm, lightDir), 0.0);
		
		return Lights [ off ].Colour * mul * diff ;
	}
	return vec3 ( 0 , 0 , 0 ) ;
}

void main ( void ) {
	vec4 colour = texture ( uTexture [ Material [ MatID ].AlbedoT ] , uv ) * Material [ MatID ].AlbedoC ;
	vec3 colour_out = vec3 ( 0.035 , 0.035 , 0.035 ) * colour.rgb ;
	for ( int i = 0 ; i < LightCount ; i++ ) {
		colour_out += ComputeLight ( i , colour.rgb ) ;
	}
	FragColor = vec4 ( colour_out , colour.a ) ;
}