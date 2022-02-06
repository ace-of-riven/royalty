#include "../level.h"

Material *traversable_materials [ 5 ] ;
Material *nontraversable_materials [ 5 ] ;

DungeonTile::DungeonTile ( int x , int y , bool traversable , unsigned int id ) {
	this->x = x;
	this->y = y;
	this->traversable = traversable;

	this->_obj = ImportGameObject ( glm::scale ( glm::vec3 ( 1e-2f ) ) , "./rc/assets/tile.fbx" ) ;
	if ( traversable )
		this->_obj->GetComponent<Mesh> ( )->material = traversable_materials [ id ] ;
	else
		this->_obj->GetComponent<Mesh> ( )->material = nontraversable_materials [ id ];
	this->_obj->transform.Move ( x , y , 0.0f ) ;
}

DungeonTile::~DungeonTile ( ) {
	delete this->_obj;
}

void InitDungeonTiles ( ) {
	char buffer [ 256 ];
	for ( unsigned int i = 0; i < 5; i++ ) {
		nontraversable_materials [ i ] = new Material ( );
		sprintf_s ( buffer , 256 , "./rc/assets/textures/wall.%d.png" , i ) ;
		nontraversable_materials [ i ]->SetAlbedo ( ImportTexture ( buffer ) );
	}
	
	for ( unsigned int i = 0; i < 5; i++ ) {
		traversable_materials [ i ] = new Material ( );
		sprintf_s ( buffer , 256 , "./rc/assets/textures/floor.%d.png" , i );
		traversable_materials [ i ]->SetAlbedo ( ImportTexture ( buffer ) );
	}
}
