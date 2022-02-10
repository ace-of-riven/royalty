layout(location = 0) in vec4 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in ivec4 aBoneI;
layout(location = 3) in vec4 aBoneW;
layout(location = 4) in vec2 aUV;
layout(location = 5) in int aMeshID;

layout(std140, binding = 1) uniform MeshProperties {
	struct {
		mat4 Bones [ MAX_BONES ] ;
	} Skeleton ;
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
	vec4 Position = vec4(0.0f);
	vec3 Normal = vec3(0.0f);
    for(int i = 0 ; i < 4 ; i++) {
        if(aBoneI[i] == -1)
			if ( i == 0 ) {
				Position = aPos;
				Normal = aNorm;
			}
			else
				break;
		mat4 Transform = Skeleton.Bones[aBoneI[i]];
		mat3 nTransform =  mat3 ( transpose ( inverse ( Skeleton.Bones[aBoneI[i]] ) ) ) ;
        Position += Skeleton.Bones[aBoneI[i]] * aPos * aBoneW[i];
        Normal += nTransform * aNorm * aBoneW[i];
    }
	gl_Position = ProjectionMatrix * ModelViewMatrix * Mesh [ aMeshID ].ModelView * Position ;
	
	uv = aUV ;
	norm = vec3 ( NormalMatrix * Normal ) ;
	pos = vec3 ( ModelViewMatrix * Mesh [ aMeshID ].ModelView * Position ) ;
	
	MatID = Mesh [ aMeshID ].MaterialID ;
}