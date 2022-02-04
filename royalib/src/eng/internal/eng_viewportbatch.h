#pragma once

#include "../eng_renderer.h"

struct ViewportMeshProperties_UBO {
	struct {
		glm::mat4 ModelView;
		int MaterialID;			// material id
		int _p0 , _p1 , _p2;		// padding
	} Mesh [ MAX_MESHES ] ;
};

struct ViewportMatProperties_UBO {
	struct {
		glm::vec4 albedo_c;		// albedo colour
		int albedo_t;			// albedo texture
		int _p0 , _p1 , _p2 ;		// padding
	} Material [ MAX_MATERIALS ];
};

struct ViewportRendererBatch {
	ViewportRendererBatch ( GPU_Shader *shader );

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

	int RegisterTexture ( GPU_Texture *texture ) ;
	// Attention this does not register the material's textures
	int RegisterMaterial ( Material *material ) ;

	bool HasSpaceForTexture ( const GPU_Texture *texure ) ;
	bool HasSpaceForMaterial ( const Material *material ) ;

	bool HasSpaceForMesh ( const Mesh *mesh );
};