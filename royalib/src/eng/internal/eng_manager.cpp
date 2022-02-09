#include "../eng_manager.h"
#include "../eng_proctor.h"
#include "../eng_renderer.h"
#include "../debug/eng_dbg_renderer.h"

EngineManager *ENG_Royalty;

void EngineManager::Register ( Proctor *proctor ) {
	proctors.push_back ( proctor ) ;
}

void EngineManager::Destroy ( Proctor *proctor ) {
	auto itr = std::find ( proctors.begin ( ) , proctors.end ( ) , proctor ) ;
	if ( itr != proctors.end ( ) )
		proctors.erase ( itr );
	else
		printf ( "EngineManager::Destroy out of bounds exception.\n" ) ;
}

void EngineManager::Update ( double deltaTime ) {
	ENG_DebugRenderer->Begin ( );
	ENG_ViewportRenderer->Begin ( ) ;
	for ( auto &proc : proctors )
		proc->Update ( deltaTime ) ;
	ENG_ViewportRenderer->Flush ( );
	ENG_DebugRenderer->Flush ( );
}
