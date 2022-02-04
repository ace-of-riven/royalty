#pragma once

#include "eng_proctor.h"

#include <string>

class GameObject : public Proctor {
	unsigned int id;
	std::string name;
public:
	GameObject ( const std::string& name ) ;

	int ComponentStack ( int comp );

	inline unsigned int GetID ( ) const { return id; }
};
