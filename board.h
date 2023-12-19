#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <ctype.h>
#include <vector>


enum Piece {
	None, Pawn, Knight, Bishop, Rook, Queen, King
};

enum Color {
	White, Black
};

/// <summary>
/// Easy way to find by name what square via index
/// Starts on h1 goes down to a8
/// </summary>
const std::string SquareNames[64]{
	"h1", "g1", "f1", "e1", "d1", "c1", "b1", "a1",
	"h2", "g2", "f2", "e2", "d2", "c2", "b2", "a2",
	"h3", "g3", "f3", "e3", "d3", "c3", "b3", "a3",
	"h4", "g4", "f4", "e4", "d4", "c4", "b4", "a4",
	"h5", "g5", "f5", "e5", "d5", "c5", "b5", "a5",
	"h6", "g6", "f6", "e6", "d6", "c6", "b6", "a6",
	"h7", "g7", "f7", "e7", "d7", "c7", "b7", "a7",
	"h8", "g8", "f8", "e8", "d8", "c8", "b8", "a8",
};

/// <summary>
/// Easy way to access square number via name
/// Starts on h1 goes down to a8
/// </summary>
enum Square {
	h1, g1, f1, e1, d1, c1, b1, a1,
	h2, g2, f2, e2, d2, c2, b2, a2,
	h3, g3, f3, e3, d3, c3, b3, a3,
	h4, g4, f4, e4, d4, c4, b4, a4,
	h5, g5, f5, e5, d5, c5, b5, a5,
	h6, g6, f6, e6, d6, c6, b6, a6,
	h7, g7, f7, e7, d7, c7, b7, a7,
	h8, g8, f8, e8, d8, c8, b8, a8,
};

class BaseBoard {
	
public:
	Piece board[64]{
		None,None,None,None,None,None,None,None,
		None,None,None,None,None,None,None,None,
		None,None,None,None,None,None,None,None,
		None,None,None,None,None,None,None,None,
		None,None,None,None,None,None,None,None,
		None,None,None,None,None,None,None,None,
		None,None,None,None,None,None,None,None,
		None,None,None,None,None,None,None,None
	};
	Color color[64]{
		White, White, White, White, White, White, White, White,
		White, White, White, White, White, White, White, White,
		White, White, White, White, White, White, White, White,
		White, White, White, White, White, White, White, White,
		White, White, White, White, White, White, White, White,
		White, White, White, White, White, White, White, White,
		White, White, White, White, White, White, White, White,
		White, White, White, White, White, White, White, White
	};
	unsigned char WhiteCastling = 0; // K = 1, Q = 2
	unsigned char BlackCastling = 0; // K = 1, Q = 2
	Color turn = White;
	Square enPassantSq = a8; // if it's a8, then it's none
	int fiftyMoveRule = 0; // half-moves since last pawn move or capture
	int fullMoveCounter = 1;

	void loadFromFEN(const std::string fen);
	void publishFEN();
	Piece pieceAt(Square sq);
	void resetBoard();

	
	

protected:

	void clearBoard();
	void fillSquare(Color c, Piece p, Square sq);
	void clearSquare(Square sq);



};

enum SPECIAL {
	NOT_SPECIAL,
	PROMOTION_KNIGHT,
	PROMOTION_BISHOP,
	PROMOTION_ROOK,
	PROMOTION_QUEEN,
	WHITE_KINGSIDE_CASTLE,
	WHITE_QUEENSIDE_CASTLE,
	BLACK_KINGSIDE_CASTLE,
	BLACK_QUEENSIDE_CASTLE,
	WHITE_ENPASSANT,
	BLACK_ENPASSANT,
	WHITE_PAWNTWOSQUARES,
	BLACK_PAWNTWOSQUARES,
};

class Move {
public:
	Square from = a8;
	Square to = a8;
	SPECIAL special = NOT_SPECIAL;
	
	void readFromUCI(const std::string str);
	Move() = default;
	Move(Square f, Square t, SPECIAL spec); // simple constructor for move
	Move(int f, int t); // rudamentary constructor for move (why not)
	Move(int f, int t, SPECIAL spec); // rudamentary constructor with special!

	friend std::ostream& operator<<(std::ostream& out, const Move& mv);
};

class Board : public BaseBoard {

public:
	std::vector<Move> move_stack{};
	std::vector<Move> legal_moves{};
	

	std::vector<Move> pseudo_legal_moves{};
	void gen_pseudo_legal_moves();
	void push(Move mv);

private:
	

};


