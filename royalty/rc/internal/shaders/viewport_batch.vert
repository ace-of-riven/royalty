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

out vec2 uv;
out vec3 norm;

flat out int MatID ;

void main ( void ) {
	gl_Position = ProjectionMatrix * ModelViewMatrix * Mesh [ aMeshID ].ModelView * aPos ;
	
	uv = aUV ;
	norm = aNorm ;
	
	MatID = Mesh [ aMeshID ].MaterialID ;
}