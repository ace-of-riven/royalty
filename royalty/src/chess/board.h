#pragma once

#include "config.h"

#include <string>

enum fBoard {
	TURN_WHITE = FLAG_WHITE ,
	TURN_BLACK = FLAG_BLACK ,
};

class Board {
	unsigned char board [ 8 ][ 8 ] ;

	unsigned char flag;
public:
	Board ( ) ;
	Board ( const std::string &fen ) ;
	Board ( const Board &other ) ;

	void init ( const std::string &fen );
	std::string genfen ( ) const;

	// 1-indexed
	inline iPiece piece_id ( unsigned int x , unsigned int y ) const {
		return ( iPiece ) ( board [ x - 1 ][ y - 1 ] & 0x0F ) ;
	}

	// 1-indexed
	inline iPiece piece_type ( unsigned int x , unsigned int y ) const {
		return ( iPiece ) ( board [ x - 1 ][ y - 1 ] & 0xF0 );
	}

	// true if white are playing
	inline bool turn ( ) const {
		return flag & TURN_WHITE;
	}

	// 1-indexed
	bool move ( unsigned int fromx ,  unsigned int fromy , unsigned int tox , unsigned int toy ) ;
};

char PieceToString ( unsigned char c );
unsigned char StringToPiece ( char c );
