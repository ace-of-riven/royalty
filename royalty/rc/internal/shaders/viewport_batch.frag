out vec4 FragColor;

layout(std140) uniform MaterialProperties {
	struct {
		vec4 AlbedoC ;
		int AlbedoT ;
	} Material [ MAX_MATERIALS ] ;
};

uniform sampler2D uTexture [ MAX_FRAG_TEXTURES ] ;

in vec2 uv;

flat in int MatID ;

void main ( void ) {
	FragColor = texture ( uTexture [ Material [ MatID ].AlbedoT ] , uv ) * Material [ MatID ].AlbedoC ;
}