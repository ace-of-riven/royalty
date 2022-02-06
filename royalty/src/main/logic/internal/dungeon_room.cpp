#include "../level.h"

DungeonRoom::DungeonRoom ( unsigned int orientation ) {
	for ( int x = -12; x <= 12; x++ ) {
		for ( int y = -12; y <= 12; y++ ) {
			tiles [ x + 12 ][ y + 12 ] = NULL;

			if ( ( x == -12 or x == 12 or y == -12 or y == 12 ) ) {
				// we are at the center of the horizontal axis
				if ( abs ( x ) <= 2 && ( orientation & ( DUNGEON_TOP | DUNGEON_BOTTOM ) ) ) {
					// we are at the top
					if ( orientation & DUNGEON_TOP and y > 0 )
						tiles [ x + 12 ][ y + 12 ] = new DungeonTile ( x , y , true , rand ( ) % 5 );
					// we are at the bottom
					if ( orientation & DUNGEON_BOTTOM and y < 0 )
						tiles [ x + 12 ][ y + 12 ] = new DungeonTile ( x , y , true , rand ( ) % 5 );
				}
				// we are at the center of the vertical axis
				else if ( abs ( y ) <= 2 && ( orientation & ( DUNGEON_LEFT | DUNGEON_RIGHT ) ) ) {
					// we are at the left
					if ( orientation & DUNGEON_LEFT and x < 0 )
						tiles [ x + 12 ][ y + 12 ] = new DungeonTile ( x , y , true , rand ( ) % 5 );
					// we are at the right
					if ( orientation & DUNGEON_RIGHT and x > 0 )
						tiles [ x + 12 ][ y + 12 ] = new DungeonTile ( x , y , true , rand ( ) % 5 );
				}
				else {
					tiles [ x + 12 ][ y + 12 ] = new DungeonTile ( x , y , false , rand ( ) % 5 );
				}
			}
			else {
				tiles [ x + 12 ][ y + 12 ] = new DungeonTile ( x , y , true , rand ( ) % 5 );
			}

			if ( tiles [ x + 12 ] [ y + 12 ] == NULL ) {
				tiles [ x + 12 ][ y + 12 ] = new DungeonTile ( x , y , false , rand ( ) % 5 );
			}
		}
	}
}
