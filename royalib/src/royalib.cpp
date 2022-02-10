#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb-master/stb_image.h"

#include "royalib.h"

std::chrono::time_point<std::chrono::system_clock> first_upd;
std::chrono::time_point<std::chrono::system_clock> last_upd;

void ROYALTY_init ( ) {
	ENG_Royalty = new EngineManager ( );
	ENG_ViewportRenderer = new ViewportRenderer ( ) ;
	ENG_DebugRenderer = new DebugRenderer ( ) ;
	first_upd = last_upd = std::chrono::system_clock::now ( );
}

void ROYALTY_update ( ) {
	auto curr_upd = std::chrono::system_clock::now ( );
	double deltaTime = std::chrono::duration<double> ( curr_upd - last_upd ).count ( ) ;
	GPU_matrix_push ( ) ;
	GPU_matrix_push_projection ( ) ;

	ENG_Royalty->Update ( deltaTime ) ;

	GPU_matrix_pop_projection ( );
	GPU_matrix_pop ( );
	last_upd = curr_upd;
}

void ROYALTY_exit ( ) {
	delete ENG_DebugRenderer;
	delete ENG_ViewportRenderer;
	delete ENG_Royalty;
}

double ROYALTY_time ( ) {
	auto curr_upd = std::chrono::system_clock::now ( );
	return std::chrono::duration<double> ( curr_upd - first_upd ).count ( );
}

//

struct {
	struct {
		int x , y;
		int dx , dy;
	} mouse ;
} ROYALTY_global ;

void ROYALTY_MouseUpdate ( int x , int y ) {
	ROYALTY_global.mouse.dx = x - ROYALTY_global.mouse.x;
	ROYALTY_global.mouse.dy = y - ROYALTY_global.mouse.y;
	ROYALTY_global.mouse.x = x;
	ROYALTY_global.mouse.y = y;
}

glm::vec2 ROYALTY_Mouse ( ) {
	int coords [ 4 ];
	GPU_viewport_size_get_i ( coords );
	return glm::vec2 ( ( float ( ROYALTY_global.mouse.x * 2 ) / coords [ 2 ] ) - 1.0f ,
			   1.0f - ( float ( ROYALTY_global.mouse.y * 2 ) / coords [ 3 ] ) );
}

glm::vec2 ROYALTY_DeltaMouse ( ) {
	return glm::vec2 ( ROYALTY_global.mouse.dx , -ROYALTY_global.mouse.dy ) ;
}

float ROYALTY_MouseX ( ) {
	int coords [ 4 ];
	GPU_viewport_size_get_i ( coords );
	return ( float ( ROYALTY_global.mouse.x * 2 ) / coords [ 2 ] ) - 1.0f ;
}

float ROYALTY_MouseY ( ) {
	int coords [ 4 ];
	GPU_viewport_size_get_i ( coords );
	return 1.0f - ( float ( ROYALTY_global.mouse.y * 2 ) / coords [ 3 ] ) ;
}
