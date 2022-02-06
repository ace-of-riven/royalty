#pragma once

#include <royalib.h>

/*
* We are gonna define a dungeon room to have a 25x25 grid of individual pieces of "quads"
* and every of these quads will have a distinct texture to them and will be either traversable or non-traversable
*/

class DungeonTile;
class DungeonRoom;

enum eDungeonOrientation {
	DUNGEON_LEFT = 1,
	DUNGEON_TOP = 2,
	DUNGEON_RIGHT = 4,
	DUNGEON_BOTTOM = 8,
};

class DungeonTile {
	// the actuall object defined for our engine so that this tile can be visible
	GameObject *_obj;

	// whether the player can stand on it
	bool traversable;

	// location of this tile inside the room
	short x , y;
public:
	DungeonTile ( int x , int y , bool traversable , unsigned int id ) ;
	~DungeonTile ( ) ;
};

class DungeonRoom {
	DungeonTile *tiles [ 25 ][ 25 ] ;
public:
	// where are the entrances at
	DungeonRoom ( unsigned int orientation ) ;
};

void InitDungeonTiles ( ) ;
