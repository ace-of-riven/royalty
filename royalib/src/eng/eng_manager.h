#pragma once

#include <vector>

class Proctor;

class EngineManager {
	std::vector<Proctor *> proctors;
public:
	void Register ( Proctor *proctor ) ;
	void Destroy ( Proctor *proctor );

	void Update ( double deltaTime ) ;
} ;

extern EngineManager *ENG_Royalty ;
