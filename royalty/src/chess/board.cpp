#include "board.h"

char PieceToString ( unsigned char c ) {
	switch ( c ) {
		case ID_KING | FLAG_BLACK: return 'k';
		case ID_KING | FLAG_WHITE: return 'K';
		case ID_PAWN | FLAG_BLACK: return 'p';
		case ID_PAWN | FLAG_WHITE: return 'P';
		case ID_KNIGHT | FLAG_BLACK: return 'n';
		case ID_KNIGHT | FLAG_WHITE: return 'N';
		case ID_BISHOP | FLAG_BLACK: return 'b';
		case ID_BISHOP | FLAG_WHITE: return 'B';
		case ID_ROOK | FLAG_BLACK: return 'r';
		case ID_ROOK | FLAG_WHITE: return 'R';
		case ID_QUEEN | FLAG_BLACK: return 'q';
		case ID_QUEEN | FLAG_WHITE: return 'Q';
	}
	return 0;
}

unsigned char StringToPiece ( char c ) {
	switch ( c ) {
		case 'k': return ID_KING | FLAG_BLACK;
		case 'K': return ID_KING | FLAG_WHITE;
		case 'p': return ID_PAWN | FLAG_BLACK;
		case 'P': return ID_PAWN | FLAG_WHITE;
		case 'n': return ID_KNIGHT | FLAG_BLACK;
		case 'N': return ID_KNIGHT | FLAG_WHITE;
		case 'b': return ID_BISHOP | FLAG_BLACK;
		case 'B': return ID_BISHOP | FLAG_WHITE;
		case 'r': return ID_ROOK | FLAG_BLACK;
		case 'R': return ID_ROOK | FLAG_WHITE;
		case 'q': return ID_QUEEN | FLAG_BLACK;
		case 'Q': return ID_QUEEN | FLAG_WHITE;
	}
	return ID_NONE;
}

void Board::init ( const std::string &fen ) {
	int file = 0 , rank = 0 ;
	for ( unsigned int i = 0; i < 8; i++ )
	for ( unsigned int j = 0; j < 8; j++ )
		board [ i ][ j ] = ID_NONE;
	size_t i = 0;
	bool finished = false;
	for ( ; finished == false and i < fen.length ( ); i++ ) {
		switch ( fen [ i ] ) {
			case '/': 
				file = 0;
				rank++;
			break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				file += fen [ i ] - '0' ;
			break;
			case ' ':
				finished = true;
			break;
			default:
				board [ file ][ rank ] = StringToPiece ( fen [ i ] ) ;
				file++;
			break;
		}
	}
	for ( ; i < fen.length ( ); i++ ) {
		switch ( fen [ i ] ) {
			case 'w':
				flag = TURN_WHITE;
			return;
			case 'b':
				flag = TURN_BLACK;
			return;
		}
	}
}

std::string Board::genfen ( ) const {
	std::string fen = "";
	for ( int rank = 0; rank < 8; rank++ ) {
		// count empty fields
		int empty = 0;
		// empty string for each rank
		std::string rankFen = "";
		for ( int file = 0; file < 8; file++ ) {
			if ( board [ file ][ rank ] == ID_NONE ) {
				empty++;
			}
			else {
				// add the number to the fen if not zero.
				if ( empty != 0 ) rankFen += std::to_string ( empty );
				// add the letter to the fen
				rankFen += PieceToString ( board [ file ][ rank ] );
				// reset the empty
				empty = 0;
			}
		}
		// add the number to the fen if not zero.
		if ( empty != 0 ) rankFen += empty;
		// add the rank to the fen
		fen += rankFen;
		// add rank separator. If last then add a space
		if ( !( rank == 7 ) ) {
			fen += "/";
		}
		else {
			fen += " ";
		}
	}
	if ( flag & TURN_WHITE )
		fen += "w";
	else
		fen += "b";
	return fen;
}

Board::Board ( ) : flag ( TURN_WHITE ) {
	init ( "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w" );
}

Board::Board ( const std::string &fen ) {
	init ( fen ) ;
}

Board::Board ( const Board &other ) : flag ( other.flag ) {
	init ( other.genfen ( ) ) ;
}

bool Board::move ( unsigned int fromx , unsigned int fromy , unsigned int tox , unsigned int toy ) {
	if ( 0 < fromx and fromx < 9 and 0 < fromy and fromy < 9 ){
	if ( 0 < tox and tox < 9 and 0 < toy and toy < 9 ) {
	if ( fromx != tox or fromy != toy ) {
	if ( piece_type ( fromx , fromy ) != piece_type ( tox , toy ) ) {
	if ( piece_type ( fromx , fromy ) & flag ) {
		unsigned char type = piece_type ( fromx , fromy );
		board [ tox - 1 ][ toy - 1 ] = board [ fromx - 1 ][ fromy - 1 ];
		board [ fromx - 1 ][ fromy - 1 ] = ID_NONE;
		flag &= ( ~type );
		if ( type == TURN_WHITE )
			flag |= TURN_BLACK;
		else
			flag |= TURN_WHITE;
		return true;
	} } } } }
	return false;
}
