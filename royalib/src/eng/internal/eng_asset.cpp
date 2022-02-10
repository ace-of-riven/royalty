#include "../eng_asset.h"

#include "../eng_renderer.h"

#include <stdlib.h> 
#include <stdio.h>
#include <map>

#include "../../../ext/stb-master/stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

static inline glm::vec3 vec3_cast ( const aiVector3D &v ) { return glm::vec3 ( v.x , v.y , v.z ); }
static inline glm::vec2 vec2_cast ( const aiVector3D &v ) { return glm::vec2 ( v.x , v.y ); }
static inline glm::quat quat_cast ( const aiQuaternion &q ) { return glm::quat ( q.w , q.x , q.y , q.z ); }
static inline glm::mat4 mat4_cast ( const aiMatrix4x4 &m ) { return glm::transpose ( glm::make_mat4 ( &m.a1 ) ); }

struct {
	std::map<std::string , Texture *> iTexture ;
} ImportedAssets ;

std::string ConvertPath ( const std::string &path ) {
	char Buffer [ 1024 ] ;
	GetFullPathNameA ( path.c_str ( ) , 1024 , Buffer , NULL ) ;
	return Buffer;
}

void ClearAllAssets ( ) {
	for ( auto texture : ImportedAssets.iTexture )
		delete texture.second ;
	ImportedAssets.iTexture.clear ( ) ;
}

Texture *ImportTexture ( const std::string &name ) {
	std::string real = ConvertPath ( name ) ;
	if ( ImportedAssets.iTexture.find ( real ) != ImportedAssets.iTexture.end ( ) )
		return ImportedAssets.iTexture [ real ] ;
	int width , height , channels;
	unsigned char *img = stbi_load ( real.c_str ( ) , &width , &height , &channels , 4 ) ;
	if ( img == NULL ) {
		printf ( "Error loading the image\n" );
		return NULL;
	}
	Texture *out = ImportedAssets.iTexture [ real ] = new Texture ( width , height , channels , img ) ;
	free ( img ) ;
	return out ;
}

Mesh *ProcessMesh ( const glm::mat4 &transform , GameObject *obj , aiMesh *mesh , const aiScene *scene ) {
	std::vector<MeshVertex> vertices;
	std::vector<unsigned int> indices;

	for ( unsigned int i = 0; i < mesh->mNumVertices; i++ )
	{
		MeshVertex vertex;
		// process vertex positions, normals and texture coordinates
		vertex.coord.x = mesh->mVertices [ i ].x;
		vertex.coord.y = mesh->mVertices [ i ].y;
		vertex.coord.z = mesh->mVertices [ i ].z;
		vertex.coord.w = 1.0f;

		vertex.norm.x = mesh->mNormals [ i ].x;
		vertex.norm.y = mesh->mNormals [ i ].y;
		vertex.norm.z = mesh->mNormals [ i ].z;

		vertex.bone_i [ 0 ] = vertex.bone_i [ 1 ] = vertex.bone_i [ 2 ] = vertex.bone_i [ 3 ] = -1;
		vertex.bone_w [ 0 ] = vertex.bone_w [ 1 ] = vertex.bone_w [ 2 ] = vertex.bone_w [ 3 ] = 0.0f;

		// does the mesh contain texture coordinates? 
		if ( mesh->mTextureCoords [ 0 ] ) {
			vertex.uv.x = mesh->mTextureCoords [ 0 ][ i ].x;
			vertex.uv.y = mesh->mTextureCoords [ 0 ][ i ].y;
		}

		vertices.push_back ( vertex );
	}
	// process indices
	for ( unsigned int i = 0; i < mesh->mNumFaces; i++ )
	{
		aiFace face = mesh->mFaces [ i ];
		for ( unsigned int j = 0; j < face.mNumIndices; j++ )
			indices.push_back ( face.mIndices [ j ] );
	}

	if ( mesh->HasBones ( ) ) {
		Skeleton *skeleton = obj->GetComponent<Skeleton> ( );
		if ( skeleton == NULL )
			obj->AddComponent<Skeleton> ( skeleton = new Skeleton ( ) ) ;
		for ( unsigned int i = 0; i < mesh->mNumBones; i++ ) {
			unsigned int bone_id = skeleton->GetBone_ensure ( mesh->mBones [ i ]->mName.C_Str ( ) , mat4_cast ( mesh->mBones [ i ]->mOffsetMatrix ) )->GetID ( ) ;
			for ( unsigned int j = 0; j < mesh->mBones [ i ]->mNumWeights; j++ ) {
				float w = mesh->mBones [ i ]->mWeights [ j ].mWeight ;
				unsigned int v = mesh->mBones [ i ]->mWeights [ j ].mVertexId ;

				// assign this bone to the first empty slot in the vertex `v`
				for ( int k = 0; k < 4; k++ ) {
					if ( vertices [ v ].bone_i [ k ] == -1 ) {
						vertices [ v ].bone_i [ k ] = bone_id;
						vertices [ v ].bone_w [ k ] = w;
						break;
					}
				}
			}
		}
	}
	
	Mesh *res = new Mesh ( vertices , indices );

	res->transform.FromMatrix ( transform ) ;

	return res;
}

void ProcessNode ( const glm::mat4 &transform , GameObject *obj , aiNode *node , const aiScene *scene ) {
	glm::mat4 curr;

	if ( node == scene->mRootNode )
		curr = transform * mat4_cast ( node->mTransformation.Inverse ( ) );
	else
		curr = transform * mat4_cast ( node->mTransformation );
	// process all the node's meshes (if any)
	for ( unsigned int i = 0; i < node->mNumMeshes; i++ ) {
		aiMesh *mesh = scene->mMeshes [ node->mMeshes [ i ] ];
		obj->AddComponent<Mesh> ( ProcessMesh ( curr , obj , mesh , scene ) );
	}
	// then do the same for each of its children
	for ( unsigned int i = 0; i < node->mNumChildren; i++ )
		ProcessNode ( curr , obj , node->mChildren [ i ] , scene );
}

GameObject *ImportGameObject ( const glm::mat4 &transform , const std::string &name , bool fix ) {
	std::string real = ConvertPath ( name );
	Assimp::Importer importer;

	importer.SetPropertyInteger ( AI_CONFIG_PP_SLM_VERTEX_LIMIT , MAX_VERTICES );

	const aiScene *scene;

	if ( fix )
		scene = importer.ReadFile ( real , aiProcessPreset_TargetRealtime_Fast | aiProcess_SplitLargeMeshes | aiProcess_LimitBoneWeights );
	else
		scene = importer.ReadFile ( real , aiProcess_Triangulate | aiProcess_SplitLargeMeshes | aiProcess_LimitBoneWeights );

	if ( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) {
		printf ( "ERROR::ASSIMP::%s\n" , importer.GetErrorString ( ) );
		return NULL;
	}
	
	GameObject *obj = new GameObject ( scene->mName.C_Str ( ) ) ;

	ProcessNode ( transform , obj , scene->mRootNode , scene ) ;

	importer.FreeScene ( ) ;
	return obj;
}
