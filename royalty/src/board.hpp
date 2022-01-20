// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// ChessBoard.hpp - ChessBoard 
// (Representing implementation of a Chess game engine)

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include <iostream>
#include <string>
#include <stdexcept>

#include "chess/header/ChessErrHandler.hpp"
#include "chess/header/ChessInfo.hpp"

#include "chess/header/Piece.hpp"
#include "chess/header/EmptyPiece.hpp"
#include "chess/header/King.hpp"
#include "chess/header/Queen.hpp"
#include "chess/header/Bishop.hpp"
#include "chess/header/Rook.hpp"
#include "chess/header/Knight.hpp"
#include "chess/header/Pawn.hpp"

using namespace std;

/* Improving clarity - the map of string (file & rank) to (ref. to) Piece would
                       be simply known as Board (as it represents a board)
*/
typedef map<string, Piece*> Board;

class ChessBoard {

/* Contains knowledge of:
   board - situation of chess board at that instant
   errorHander - an error handler to handle invalid submitted moves
   piecePlaceholder - a Null Piece (EmptyPiece) for those who might need it
   boolean flags - obvious in function by their names, right?
*/
  private:
    Board* board;
    ChessErrHandler* errorHandler;
    Piece* piecePlaceholder;

    bool isWhiteTurn = true;
    bool isInCheck = false;
    bool hasEnded = false;

  public:
    ChessBoard();
    ~ChessBoard();

    void resetBoard();
    void submitMove(const char* fromSquare, const char* toSquare);

    inline bool whiteTurn ( ) const { return isWhiteTurn; }
    inline bool blackTurn ( ) const { return !isWhiteTurn; }

    Piece *at ( char i , char j ) const ;
    Piece *at ( std::string l ) const ;

  private:
/* Pre-defined setter of the boolean flags, internal use only
   (Hiding object fields from being changed by public methods directly)
*/
    void getANewBoard ();
    void makeGameInCheck ();
    void makeGameNotInCheck ();
    void beginAGame ();
    void endTheGame ();
    void makeWhiteGoesNext ();

/* N.B.: To reduce cohesion between methods and the class, class field are
         passed in as arguments of individual methods, aiming to allow methods
         to function elsewhere when moved to other classes/ programs
*/
/* Pre-move checking methods:
   Multiple layers of check if input are valid move on board
*/
    bool gameCanContinue (string sourceFileRank, string destFileRank);
    bool sourceAndDestIsValid (string sourceFileRank, string destFileRank);
    bool withinChessBoard (string fileRank);
    bool sourceIsNotEmpty (string sourceFileRank, Board* board);
    bool isCurrentPlayerPiece (bool isWhiteTurn, Piece* piece, 
                               string sourceFileRank);
    bool pieceMoveIsValid (int returnCode, Piece* piece,
                           string sourceFileRank, string destFileRank);
    bool pieceMoveKeepsKingSafe (bool isWhiteTurn, Piece* piece,
      string sourceFileRank, string destFileRank, Board* sandboxBoard);

// Responsible in calling the handler to print out *helpful* error messages
    void handleInvalidMove (int returnCode, Piece* piece,
                            string sourceFileRank, string destFileRank);

/* Pre-move/ post-move (pure) checking methods:
   Checks if the given side's king is safe from rivalry on given board, 
     and if the given side have valid move based on given board
*/
    bool kingIsSafeFromRivalry (bool isWhiteTurn, Board* board);
    bool playerHaveValidMove (bool isWhiteTurn, Board* board);
    string findPlayersKingFileRank (bool isWhiteTurn, Board* board);

/* In-move methods that make side-effect on chess board:
   Move the piece on source file and rank on a given board as in how one does
     in real life (Method differs in if it returns the captured piece or not)
*/
    Piece* tryMoveAndReturnCaptured 
      (string sourceFileRank, string destFileRank, Board* board);
    void confirmMoveOnBoard
      (string sourceFileRank, string destFileRank, Board* board);

// Doesn't require much explanation for the following three methods right?
    void switchPlayers ();

    Board* cloneBoard (Board* board);
    void deepCleanBoard (Board* board);

// Printing methods, in both text and graphics, on stdout
    bool showMoveAndCheckIfGameCanContinue
      (Piece* piece, string sourceFileRank, Piece* capturedPiece, 
       string destFileRank, bool isWhiteTurn, Board* board);

    void printMove (Piece* piece, string sourceFileRank, string destFileRank);
    void printCapture (Piece* capturedPiece);
    void printCheck ();
    void printCheckmate (bool isWhitePlayer);
    void printStalemate ();
};

#endif
