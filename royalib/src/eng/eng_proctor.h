#pragma once

#include "eng_component.h"

#include <map>
#include <vector>

#define PROCTOR_MAX			(SHRT_MAX*16)

class Proctor {
	std::map<int , std::vector<Component *>> components;
protected:
	void Push ( Component *component );
	void Pop ( Component *component );
public:
	Proctor ( ) ;
	virtual ~Proctor ( ) ;

	virtual int ComponentStack ( int comp );

	virtual void OnUpdate ( double deltaTime ) { }

	void Update ( double deltaTime ) ;

	// get

	template <typename T>
	inline const T *GetComponent ( ) const {
		int C = T ( ).Identifier ( );
		auto itr = components.find ( C );
		if ( itr != components.end ( ) )
			if ( itr->second.size ( ) )
				return ( const T * ) itr->second [ 0 ];
		return NULL;
	}

	template <typename T>
	inline T *GetComponent ( ) {
		int C = T ( ).Identifier ( );
		auto itr = components.find ( C );
		if ( itr != components.end ( ) )
			if ( itr->second.size ( ) )
				return ( T * ) itr->second [ 0 ];
		return NULL;
	}

	template <typename T>
	inline const std::vector<Component *> *GetComponents ( ) const {
		int C = T ( ).Identifier ( );
		auto itr = components.find ( C );
		if ( itr != components.end ( ) )
			if ( itr->second.size ( ) )
				return &itr->second;
		return NULL;
	}

	template <typename T>
	inline std::vector<Component *> *GetComponents ( ) {
		int C = T ( ).Identifier ( );
		auto itr = components.find ( C );
		if ( itr != components.end ( ) )
			if ( itr->second.size ( ) )
				return &itr->second;
		return NULL;
	}

	// add

	template <typename T>
	inline Proctor &AddComponent ( T &component ) {
		int C = T ( ).Identifier ( );
		Push ( &component );
		return *this;
	}

	template <typename T>
	inline Proctor &AddComponent ( T *component ) {
		int C = T ( ).Identifier ( );
		Push ( component );
		return *this;
	}

	// rem

	template <typename T>
	inline void RemoveComponent ( ) {
		int C = T ( ).Identifier ( );
		Pop ( components [ C ][ 0 ] );
	}

	template <typename T>
	inline void RemoveComponent ( T *component ) {
		int C = T ( ).Identifier ( );
		Pop ( component );
	}

	// del

	template <typename T>
	inline void DeleteComponent ( ) {
		int C = T ( ).Identifier ( );
		Component *component = components [ C ][ 0 ];
		Pop ( component );
		delete component;
	}

	template <typename T>
	inline void DeleteComponent ( T *component ) {
		int C = T ( ).Identifier ( );
		Pop ( component );
		delete component;
	}

};
