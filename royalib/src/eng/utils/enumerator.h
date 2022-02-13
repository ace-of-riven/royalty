#pragma once

// simple class type to int converter
template<int T>
class Enumerator {
public:
	virtual ~Enumerator ( ) = default;

	static int Identifier ( );
};
