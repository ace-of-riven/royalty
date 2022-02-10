#pragma once

#include "../eng_renderer.h"
#include "../eng_skeleton.h"

struct MeshProperties_UBO {
	struct Skeleton {
		ALIGN_STD140 glm::mat4 Bones [ MAX_BONES ];
	};

	struct Mesh {
		ALIGN_STD140 glm::mat4 ModelView;
		ALIGN_STD140 int MaterialID;			// material id
	} ;

	Skeleton skeleton;

	// add this to a vector so that everytime we copy this to the GPU we only copy the data that we actually need
	std::vector<Mesh> data;
};

struct MatProperties_UBO {
	struct Material {
		ALIGN_STD140 glm::vec4 albedo_c;		// albedo colour
		ALIGN_STD140 int albedo_t;			// albedo texture
	} ;
	// add this to a vector so that everytime we copy this to the GPU we only copy the data that we actually need
	std::vector<Material> data;
};

class RendererBatch {
	GPU_Shader *shader;

	GPU_VertBuf *vbo;
	GPU_IndexBuf *ibo;
	GPU_Batch *batch;

	GPU_IndexBufBuilder *builder;

	MeshProperties_UBO mesh_properties;
	MatProperties_UBO mat_properties;

	GPUPrimType prim;

	std::vector<Material *> materials;

	std::vector<GPU_Texture *> textures;

	unsigned int indices_count;
	unsigned int vertices_count;
	unsigned int mesh_count;
	unsigned int bones_count;

	// current skeleton bone offsets
	unsigned int skeleton_offset;

	std::map<const Skeleton * , unsigned int> skeletons;

	glm::mat4 transform;

	int aPos , aNorm , aUV , aMeshID , aBoneI , aBoneW;
protected:
	int RegisterTexture ( GPU_Texture *texture );
	// Attention this does not register the material's textures
	int RegisterMaterial ( Material *material );
public:
	RendererBatch ( GPUPrimType prim , GPU_Shader *shader );
	~RendererBatch ( ) ;

	bool SelectSkeleton ( const Skeleton *skeleton ) ;

	void Clear ( ) ;
	void InsertMesh ( const Mesh *mesh ) ;
	void Upload ( GPU_UniformBuf *mesh_ubo , GPU_UniformBuf *mat_ubo ) ;
	void Render ( GPU_UniformBuf *mesh_ubo , GPU_UniformBuf *mat_ubo ) const ;

	void UpdateMatrix ( const glm::mat4& matrix ) ;

	bool HasSpaceForTexture ( const GPU_Texture *texure ) ;
	bool HasSpaceForMaterial ( const Material *material ) ;

	bool HasSpaceForMesh ( const Mesh *mesh );
};