layout(location = 0) in vec4 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aUV;
layout(location = 3) in int aMeshID;

layout(std140, binding = 1) uniform MeshProperties {
	struct {
		mat4 ModelView;
		int MaterialID;
	} Mesh [ MAX_MESHES ] ;
};

uniform mat4 ProjectionMatrix ;  
uniform mat4 ModelViewMatrix ; 
uniform mat3 NormalMatrix ; 

out vec2 uv;
out vec3 norm;
out vec3 pos;

flat out int MatID ;

void main ( void ) {
	gl_Position = ProjectionMatrix * ModelViewMatrix * Mesh [ aMeshID ].ModelView * aPos ;
	
	uv = aUV ;
	norm = vec3 ( NormalMatrix * aNorm ) ;
	pos = vec3 ( ModelViewMatrix * Mesh [ aMeshID ].ModelView * aPos ) ;
	
	MatID = Mesh [ aMeshID ].MaterialID ;
}