#pragma once

#include "renderer.h"

#define STD140_LAYOUT		__declspec(align(64))

#define MAX_VERTICES				(512*1024)
#define MAX_INDICES				(512*1024)

#define MAX_MESHES				(64)
#define MAX_MATERIALS				(32)
#define MAX_BONES				(512)
#define MAX_LIGHTS				(512)

struct MeshProperties_UBO {
	struct Mesh {
		STD140_LAYOUT glm::mat4 ModelView;		// transformation matrix
	};
	// add this to a vector so that everytime we copy this to the GPU we only copy the data that we actually need
	std::vector<Mesh> data;
};

struct MatProperties_UBO {
	struct Material {
		STD140_LAYOUT glm::vec4 albedo_c;		// albedo colour
		STD140_LAYOUT int albedo_t;			// albedo texture
	};
	// add this to a vector so that everytime we copy this to the GPU we only copy the data that we actually need
	std::vector<Material> data;
};

class Batch {
	GPU_Shader *shader;

	GPU_VertBuf *vbo;
	GPU_IndexBuf *ibo;
	GPU_Batch *batch;

	GPU_IndexBufBuilder *builder;

	MeshProperties_UBO mesh_properties;
	MatProperties_UBO mat_properties;

	GPUPrimType prim;

	std::vector<const Material *> materials;

	std::vector<GPU_Texture *> textures;

	unsigned int indices_count;
	unsigned int vertices_count;
	unsigned int mesh_count;

	glm::mat4 transform;

	int aPos , aNorm , aUV , aMeshID;
protected:
	int RegisterTexture ( GPU_Texture *texture );
	// Attention this does not register the material's textures
	int RegisterMaterial ( const Material *material );
public:
	Batch ( GPUPrimType prim , GPU_Shader *shader );
	~Batch ( );

	void Clear ( );
	void InsertMesh ( const Mesh *mesh );
	void Upload ( GPU_UniformBuf *mesh_ubo , GPU_UniformBuf *mat_ubo );
	void Render ( GPU_UniformBuf *mesh_ubo , GPU_UniformBuf *mat_ubo ) const;

	void UpdateMatrix ( const glm::mat4 &matrix );

	bool HasSpaceForTexture ( const GPU_Texture *texure );
	bool HasSpaceForMaterial ( const Material *material );

	bool HasSpaceForMesh ( const Mesh *mesh );
};