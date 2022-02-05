#pragma once

#include "eng_proctor.h"
#include "eng_transform.h"

#include <string>

class GameObject : public Proctor {
	unsigned int id;
	std::string name;
public:
	GameObject ( const std::string& name ) ;

	int ComponentStack ( int comp );

	Transform transform;

	inline unsigned int GetID ( ) const { return id; }
	inline const std::string &GetName ( ) const { return name; }
};
