#include "main.h"

#include "logic/level.h"

void MainScript::OnInit ( ) {
	InitDungeonTiles ( ) ;

	new DungeonRoom ( DUNGEON_LEFT | DUNGEON_BOTTOM | DUNGEON_TOP ) ;
}

void MainScript::OnUpdate ( double deltaTime ) {
	GPU_matrix_ortho_2d_set ( -16.0f , 16.0f , -16.0f , 16.0f ) ;

	int mouse_tile_x = ( ROYALTY_MouseX ( ) * 16 ) + 0.5f;
	int mouse_tile_y = ( ROYALTY_MouseY ( ) * 16 ) - 0.5f;
}
