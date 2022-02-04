layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in int aMeshID;

layout(std140) uniform MeshProperties {
	struct {
		mat4 ModelView;
		int MaterialID;
	} Mesh [ MAX_MESHES ] ;
};

uniform mat4 ProjectionMatrix ;

out vec2 uv;

flat out int MatID ;

void main ( void ) {
	gl_Position = Mesh [ aMeshID ].ModelView * aPos ;
	
	uv = aUV ;
	
	MatID = Mesh [ aMeshID ].MaterialID ;
}