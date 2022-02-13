#pragma once

#include "../utils/enumerator.h"
#include "../utils/transform.h"

#include "component.h"

#include <vector>
#include <map>

class Proctor {
	bool is_initialized;

	std::map<unsigned int , std::vector<Component *>> components;
protected:
	virtual unsigned int ComponentStack ( unsigned int id ) const;
public:
	Proctor ( ) ;
	~Proctor ( ) ;

	template<class T>
	bool AddComponent ( T &component ) {
		unsigned int comp_identifier = T ( ).Identifier ( );
		std::vector<Component *> &vec = components [ comp_identifier ];
		if ( vec.size ( ) < ComponentStack ( comp_identifier ) ) {
			component.Attach ( this );
			vec.push_back ( &component );
			return true;
		}
		return false;
	}

	template<class T>
	bool AddComponent ( T *component ) {
		unsigned int comp_identifier = T ( ).Identifier ( );
		std::vector<Component *> &vec = components [ comp_identifier ];
		if ( vec.size ( ) < ComponentStack ( comp_identifier ) ) {
			component->Attach ( this );
			vec.push_back ( component );
			return true;
		}
		return false;
	}

	template<class T>
	T *GetComponent ( ) const {
		unsigned int comp_identifier = T ( ).Identifier ( );
		auto itr = components.find ( comp_identifier );
		if ( itr != components.end ( ) ) {
#ifdef _DEBUG
			if ( itr->second.size ( ) > 1 )
				printf ( "WARNING Proctor::GetComponent<%d> ( ) called for stacking components.\n" , comp_identifier );
#endif
			if ( itr->second.size ( ) )
				return ( T * ) itr->second [ 0 ];
			return NULL;
		}
		return NULL;
	}

	template<class T>
	T *GetComponent ( unsigned int off ) const {
		unsigned int comp_identifier = T ( ).Identifier ( );
		auto itr = components.find ( comp_identifier );
		if ( itr != components.end ( ) ) {
			if ( off < itr->second.size ( ) )
				return ( T * ) itr->second [ off ];
			return NULL;
		}
		return NULL;
	}

	template<class T>
	const std::vector<Component *> &GetComponents ( ) const {
		unsigned int comp_identifier = T ( ).Identifier ( );
		auto itr = components.find ( comp_identifier );
		if ( itr != components.end ( ) ) {
			return itr->second;
		}
		return std::vector<Component *> ( );
	}

	template<class T>
	bool DeleteComponent ( ) {
		unsigned int comp_identifier = T ( ).Identifier ( );
		auto itr = components.find ( comp_identifier );
		if ( itr != components.end ( ) ) {
#ifdef _DEBUG
			if ( itr->second.size ( ) > 1 )
				printf ( "WARNING Proctor::DeleteComponent<%d> ( ) called for stacking components.\n" , comp_identifier );
#endif
			if ( itr->second.size ( ) ) {
				itr->second [ 0 ]->Detach ( );
				delete itr->second [ 0 ];
				itr->second.erase ( itr->second->begin ( ) );
				return true;
			}
			return false;
		}
		return false;
	}

	template<class T>
	bool DeleteComponent ( unsigned int off ) {
		unsigned int comp_identifier = T ( ).Identifier ( );
		auto itr = components.find ( comp_identifier );
		if ( itr != components.end ( ) ) {
			if ( off < itr->second.size ( ) ) {
				itr->second [ off ]->Detach ( );
				delete itr->second [ off ];
				itr->second.erase ( itr->second->begin ( ) + off );
				return true;
			}
			return false;
		}
		return false;
	}

	template<class T>
	bool DeleteComponents ( ) {
		unsigned int comp_identifier = T ( ).Identifier ( );
		auto itr = components.find ( comp_identifier );
		if ( itr != components.end ( ) ) {
			for ( auto item : itr->second ) {
				item->Detach ( );
				delete item;
			}
			components.erase ( itr );
		}
		return false;
	}

	virtual void OnInit ( ) { }
	virtual void OnUpdate ( ) { }

	void Update ( ) ;
};

void UpdateProctors ( ) ;
