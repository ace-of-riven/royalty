#include "royalib.h"

std::chrono::time_point<std::chrono::system_clock> last_upd;

void ROYALTY_init ( ) {
	ENG_Royalty = new EngineManager ( );
	ENG_ViewportRenderer = new ViewportRenderer ( ) ;
	last_upd = std::chrono::system_clock::now ( );
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
	delete ENG_ViewportRenderer;
	delete ENG_Royalty;
}
