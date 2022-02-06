#pragma once

#include "../eng_renderer.h"

struct ViewportMeshProperties_UBO {
	struct Mesh {
		glm::mat4 ModelView;
		int MaterialID;			// material id
		int _p0 , _p1 , _p2;		// padding
	} ;
	// add this to a vector so that everytime we copy this to the GPU we only copy the data that we actually need
	std::vector<Mesh> data;
};

struct ViewportMatProperties_UBO {
	struct Material {
		glm::vec4 albedo_c;		// albedo colour
		int albedo_t;			// albedo texture
		int _p0 , _p1 , _p2 ;		// padding
	} ;
	// add this to a vector so that everytime we copy this to the GPU we only copy the data that we actually need
	std::vector<Material> data;
};

class ViewportRendererBatch {
	GPU_Shader *shader;

	GPU_VertBuf *vbo;
	GPU_IndexBuf *ibo;
	GPU_Batch *batch;

	GPU_IndexBufBuilder *builder;

	ViewportMeshProperties_UBO mesh_properties;
	ViewportMatProperties_UBO mat_properties;

	std::vector<Material *> materials;

	std::vector<GPU_Texture *> textures;

	unsigned int indices_count;
	unsigned int vertices_count;
	unsigned int mesh_count;

	glm::mat4 transform;

	int aPos , aNorm , aUV , aMeshID;
protected:
	int RegisterTexture ( GPU_Texture *texture );
	// Attention this does not register the material's textures
	int RegisterMaterial ( Material *material );
public:
	ViewportRendererBatch ( GPU_Shader *shader );
	~ViewportRendererBatch ( ) ;

	void Clear ( ) ;
	void InsertMesh ( const Mesh *mesh ) ;
	void Upload ( GPU_UniformBuf *mesh_ubo , GPU_UniformBuf *mat_ubo ) ;
	void Render ( GPU_UniformBuf *mesh_ubo , GPU_UniformBuf *mat_ubo ) const ;

	void UpdateMatrix ( const glm::mat4& matrix ) ;

	bool HasSpaceForTexture ( const GPU_Texture *texure ) ;
	bool HasSpaceForMaterial ( const Material *material ) ;

	bool HasSpaceForMesh ( const Mesh *mesh );
};