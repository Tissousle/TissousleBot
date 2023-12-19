#include "board.h"



void BaseBoard::loadFromFEN(const std::string fen)
{
	using namespace std;

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
	return;
}

void BaseBoard::publishFEN()
{
	using namespace std;

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
	
	return;
}

Piece BaseBoard::pieceAt(const Square sq)
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

void BaseBoard::fillSquare(const Color c, const Piece p, const Square sq)
{
	color[sq] = c;
	board[sq] = p;
}

void BaseBoard::clearSquare(const Square sq)
{
	color[sq] = White;
	board[sq] = None;
}

void Move::readFromUCI(const std::string str)
{
	if (str.length() == 0) { return; }


	const std::string fromStr = str.substr(0, 2);
	const std::string toStr = str.substr(2, 2);

	//i think this finds the right square from the squares and sets it right
	from = static_cast<Square>(std::distance(SquareNames,std::find(std::begin(SquareNames), std::end(SquareNames), fromStr)));

	to = static_cast<Square>(std::distance(SquareNames, std::find(std::begin(SquareNames), std::end(SquareNames), toStr)));

	if (str.length() == 5) {
		switch (str[4]) {

		case 'q':
			special = PROMOTION_QUEEN;
			break;
		case 'r':
			special = PROMOTION_ROOK;
			break;
		case 'n':
			special = PROMOTION_KNIGHT;
			break;
		case 'b':
			special = PROMOTION_BISHOP;
			break;
		}
	}
}

std::vector<Move> Board::gen_pseudo_legal_moves()
{
	static const int mailbox[120] = {
	 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 -1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
	 -1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
	 -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
	 -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
	 -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
	 -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
	 -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
	 -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	};

	static const int mailbox64[64] = {
		21, 22, 23, 24, 25, 26, 27, 28,
		31, 32, 33, 34, 35, 36, 37, 38,
		41, 42, 43, 44, 45, 46, 47, 48,
		51, 52, 53, 54, 55, 56, 57, 58,
		61, 62, 63, 64, 65, 66, 67, 68,
		71, 72, 73, 74, 75, 76, 77, 78,
		81, 82, 83, 84, 85, 86, 87, 88,
		91, 92, 93, 94, 95, 96, 97, 98
	};
	
	static const int offsets[6] = { 0, 8, 4, 4, 8, 8 }; /* knight or ray directions */

	static const int offset[6][8] = {
		{   0,   0,  0,  0, 0,  0,  0,  0 },
		{ -21, -19,-12, -8, 8, 12, 19, 21 }, /* KNIGHT */
		{ -11,  -9,  9, 11, 0,  0,  0,  0 }, /* BISHOP */
		{ -10,  -1,  1, 10, 0,  0,  0,  0 }, /* ROOK */
		{ -11, -10, -9, -1, 1,  9, 10, 11 }, /* QUEEN */
		{ -11, -10, -9, -1, 1,  9, 10, 11 }  /* KING */
	};
	
	for (int i = 0; i < 64; i++) {

		if (color[i] == turn and board[i]) {

			Piece piece = board[i];

			if (not piece == Pawn) {

			}
		}
	}
	
	
	
	
	
	return std::vector<Move>();
}
