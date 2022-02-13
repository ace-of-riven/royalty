#pragma once

#include "proctor.h"
#include "mesh.h"

class GameObject : public Proctor {
	std::string name;
public:
	GameObject ( GameObject *parent , const std::string &name ) ;
	~GameObject ( ) ;

	virtual unsigned int ComponentStack ( unsigned int id ) const;
};

GameObject *FindGameObject ( const std::string &name ) ;
