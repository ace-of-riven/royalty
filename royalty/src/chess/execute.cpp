#include <iostream>
#include <vector>
#include <string>
#include "chess.h"

using namespace std;

int map_to_int(char c){
    int val;
    switch(c){
        case 'a': val=1; break;
        case 'b': val=2; break;
        case 'c': val=3; break;
        case 'd': val=4; break;
        case 'e': val=5; break;
        case 'f': val=6; break;
        case 'g': val=7; break;
        case 'h': val=8; break;
        default: val=0;
    }
    return val;
}

void allowed_moves ( Node &root , int depth ) {
	if ( depth >= MAX_DEPTH )
		return;

	int i , j;
	for ( i = 2; i < 10; i++ ) {
		for ( j = 2; j < 10; j++ ) {
			char c = root->board [ i ][ j ];

			if ( 1 == root->cur_side ) { // WHITE has moved. Looking for BLACK pieces to move
				switch ( c ) {
					case 'q': queen ( root , i , j , 1 ); break;
					case 'r': rook ( root , i , j , 1 ); break;
					case 'b': bishop ( root , i , j , 1 ); break;
					case 'n': knight ( root , i , j , 1 ); break;
					case 'p': pawn ( root , i , j , 1 ); break;
					case 'k': king ( root , i , j , 1 ); break;
				}
			}
			else { // BLACK has moved. Looking for WHITE pieces to move.
				switch ( c ) {
					case 'Q': queen ( root , i , j , 0 ); break;
					case 'R': rook ( root , i , j , 0 ); break;
					case 'B': bishop ( root , i , j , 0 ); break;
					case 'N': knight ( root , i , j , 0 ); break;
					case 'P': pawn ( root , i , j , 0 ); break;
					case 'K': king ( root , i , j , 0 ); break;
				}
			}
		}
	}
	// Iterates through each of the generated possibilities
	vector<Node>::iterator it;
	for ( it = root->next.begin ( ); it != root->next.end ( ); it++ )
		next_move ( *it , depth + 1 );
}

bool exec_player_move ( Node &root , string mv ) {
	// Mapping mv to the correct array coordinates (s,t) --> (u,v)
	int s = 8 - ( mv.c_str ( ) [ 1 ] - '0' ) + 2;
	int t = map_to_int ( mv.c_str ( ) [ 0 ] ) + 1;
	int u = 8 - ( mv.c_str ( ) [ 3 ] - '0' ) + 2;
	int v = map_to_int ( mv.c_str ( ) [ 2 ] ) + 1;

	// Replacing the target square with source square
	char source = root->board [ s ][ t ];
	char target = root->board [ u ][ v ];

	if ( same_side ( 0 , source ) == false ) {
		printf ( "not your pawn.\n" ) ;
		return false; // we tried to move a black piece
	}

	if ( same_side ( 0 , target ) ) {
		printf ( "cannot capture yourself pawn.\n" );
		return false; // we tried to capture our own piece
	}

	bool found = false;

	for ( auto state : root->next ) {
		int s1 , t1 , u1 , v1 ;
		sscanf ( state->mv.c_str ( ) , "(%d,%d)->(%d,%d)" , &s1 , &t1 , &u1 , &v1 );

		if ( s1 == s and t1 == t and u1 == u and v1 == v ) {
			found = true;
			break;
		}
	}

	if ( !found ) {
		printf ( "not a valid move.\n" );
		return false;
	}

	root->board [ u ][ v ] = source;
	root->board [ s ][ t ] = ' ';

	if ( ' ' != target )
		root->materials [ target ] -= 1;
	return true;
}
