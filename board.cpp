#include "board.h"

using namespace std;


int BaseBoard::loadFromFEN(const std::string fen)
{
	clearBoard();

	stringstream s(fen);

	string word;


	short int x = 0;
	while (s >> word) {
		switch (x) {

		case 0:
		{
			char i = 0;
			char sq = 63;
			while (word.length() > i) {
				char currentChar = word[i];
				if (isdigit(currentChar)) {
					sq -= (currentChar - '0');
				}
				else
				{
					switch (currentChar) {
					case 'p':
					{
						fillSquare(Black, Pawn, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'n':
					{
						fillSquare(Black, Knight, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'b':
					{
						fillSquare(Black, Bishop, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'r':
					{
						fillSquare(Black, Rook, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'q':
					{
						fillSquare(Black, Queen, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'k':
					{
						fillSquare(Black, King, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'P':
					{
						fillSquare(White, Pawn, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'N':
					{
						fillSquare(White, Knight, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'B':
					{
						fillSquare(White, Bishop, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'R':
					{
						fillSquare(White, Rook, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'Q':
					{
						fillSquare(White, Queen, static_cast<Square>(sq));
						sq--;
						break;
					}
					case 'K':
					{
						fillSquare(White, King, static_cast<Square>(sq));
						sq--;
						break;
					}
					default:
						break;
					}
				}
				i++;
			}

			break;

		}
		case 1:
		{
			if (word == "b") {
				sideToMove = Black;
			}
			else {
				sideToMove = White;
			}
			break;
		}
		case 2:
		{
			for (char& c : word) {
				switch (c) {
				case 'K':
					WhiteCastling += 1;
					break;
				case 'Q':
					WhiteCastling += 2;
					break;
				case 'k':
					BlackCastling += 1;
					break;
				case 'q':
					BlackCastling += 2;
					break;
				default:
					break;
				}
			}
			break;
		}
		case 3:
		{
			if (word != "-") {
				for (auto i = 0; i < 64; i++) {
					if (SquareNames[i] == word) {
						enPassantSq = static_cast<Square>(i);
						break;
					}
				}
			}
			break;
		}
		case 4:
		{
			fiftyMoveRule = stoi(word);
			break;
		}
		case 5:
		{
			//TODO move numbers
			break;
		}
		default:
			break;
		}
		x++;
	}
	return 0;
}

int BaseBoard::publishFEN()
{
	ostringstream oss;

	for (auto i = 7; i >= 0; i--) {
		int x = 0;
		for (auto j = 7; j >= 0; j--) {
			int iter = (i * 8) + j;
			if (board[iter] != None) {
				if (x) {
					oss << x;
					x = 0;
				}
				if (color[iter] == White) {
					if (board[iter] == Pawn) {
						oss << 'P';
					}
					else if (board[iter] == Knight) {
						oss << 'N';
					}
					else if (board[iter] == Bishop) {
						oss << 'B';
					}
					else if (board[iter] == Rook) {
						oss << 'R';
					}
					else if (board[iter] == Queen) {
						oss << 'Q';
					}
					else if (board[iter] == King) {
						oss << 'K';
					}
				}
				else 
				{
					if (board[iter] == Pawn) {
						oss << 'p';
					}
					else if (board[iter] == Knight) {
						oss << 'n';
					}
					else if (board[iter] == Bishop) {
						oss << 'b';
					}
					else if (board[iter] == Rook) {
						oss << 'r';
					}
					else if (board[iter] == Queen) {
						oss << 'q';
					}
					else if (board[iter] == King) {
						oss << 'k';
					}
				}

			}
			else 
			{
				x++;
			}
		}
		if (x > 0) oss << x;
		if (i != 0) oss << '/';
	}
	oss << (bool(sideToMove) ? " b " : " w ");
	if (WhiteCastling % 2 == 1) oss << "K";
	if (WhiteCastling - 2 >= 0) oss << "Q";
	if (BlackCastling % 2 == 1) oss << "k";
	if (BlackCastling - 2 >= 0) oss << "q";
	if (WhiteCastling == 0 and BlackCastling == 0) oss << "-";

	if (enPassantSq != a8) {
		oss << " " << SquareNames[enPassantSq] << " ";
	}
	else {
		oss << " - ";
	}

	oss << fiftyMoveRule << "\n";

	std::cout << oss.str();
	
	return 0;
}

Piece BaseBoard::pieceAt(Square sq)
{
	return board[static_cast<int>(sq)];
}

void BaseBoard::clearBoard()
{
	for (int i = 0; i < 64; i++) {
		board[i] = None;
		color[i] = White;
	}
	sideToMove = White;
	enPassantSq = a8;
	WhiteCastling = 0;
	BlackCastling = 0;
	fiftyMoveRule = 0;
}

void BaseBoard::fillSquare(Color c, Piece p, Square sq)
{
	color[sq] = c;
	board[sq] = p;
}

void BaseBoard::clearSquare(Square sq)
{
	color[sq] = White;
	board[sq] = None;
}

bool Move::isCapture()
{
	return false;
}
