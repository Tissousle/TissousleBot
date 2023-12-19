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
				turn = Black;
			}
			else {
				turn = White;
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
			fullMoveCounter = stoi(word);
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
	oss << (bool(turn) ? " b " : " w ");
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

	oss << fiftyMoveRule << " " << fullMoveCounter << '\n';



	std::cout << oss.str();
	
	return;
}

Piece BaseBoard::pieceAt(const Square sq)
{
	return board[static_cast<int>(sq)];
}

void BaseBoard::resetBoard()
{
	this->loadFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void BaseBoard::clearBoard()
{
	for (int i = 0; i < 64; i++) {
		board[i] = None;
		color[i] = White;
	}
	turn = White;
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

Move::Move(Square f, Square t, SPECIAL spec)
{
	from = f;
	to = t;
	special = spec;
}

Move::Move(int f, int t)
{
	from = static_cast<Square>(f);
	to = static_cast<Square>(t);
	special = NOT_SPECIAL;
}

Move::Move(int f, int t, SPECIAL spec)
{
	from = static_cast<Square>(f);
	to = static_cast<Square>(t);
	special = spec;
}

void Board::gen_pseudo_legal_moves()
{

	pseudo_legal_moves.clear();

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
	
	static const int offsets[7] = { 0, 0, 8, 4, 4, 8, 8 }; /* knight or ray directions */

	static const int offset[7][8] = {
		{   0,   0,  0,  0, 0,  0,  0,  0 }, /* None*/
		{   0,   0,  0,  0, 0,  0,  0,  0 }, /* PAWN */
		{ -21, -19,-12, -8, 8, 12, 19, 21 }, /* KNIGHT */
		{ -11,  -9,  9, 11, 0,  0,  0,  0 }, /* BISHOP */
		{ -10,  -1,  1, 10, 0,  0,  0,  0 }, /* ROOK */
		{ -11, -10, -9, -1, 1,  9, 10, 11 }, /* QUEEN */
		{ -11, -10, -9, -1, 1,  9, 10, 11 }  /* KING */
	};
	
	for (int i = 0; i < 64; i++) {

		if (color[i] == turn and board[i] != None) {

			Piece piece = board[i];

			if (piece == Pawn) {
				if (i <= 7 or i >= 56) {
					std::cout << "error in void Board::gen_pseudo_legal_moves()";
					return;
				}
				if (turn == White) {
					// we need the a8 en passant logic for white and not black because white can attack a8
					// with a pawn at some point so it'd be weird if it was take-able.
					if (i % 8 != 0 and (color[i + 7] == Black or (i + 7 == enPassantSq and enPassantSq != a8))) {
						(i + 7 == enPassantSq and enPassantSq != a8) ?
							pseudo_legal_moves.push_back(Move(i, i + 7, WHITE_ENPASSANT)): 
							pseudo_legal_moves.push_back(Move(i, i + 7));
					}
					if (i % 8 != 7 and (color[i + 9] == Black or (i + 9 == enPassantSq and enPassantSq != a8))) {
						(i + 9 == enPassantSq and enPassantSq != a8) ?
							pseudo_legal_moves.push_back(Move(i, i + 9, WHITE_ENPASSANT)):
							pseudo_legal_moves.push_back(Move(i, i + 9));
					}
					if (not board[i + 8]) {
						pseudo_legal_moves.push_back(Move(i, i + 8));
						if (i < 16 and not board[i + 16]) {
							pseudo_legal_moves.push_back(Move(i, i + 16, WHITE_PAWNTWOSQUARES));
						}
					}
				}
				else
				{
					if (i % 8 != 7 and ((color[i - 7] == White and board[i - 7]) or i - 7 == enPassantSq)) {
						i - 7 == enPassantSq ?
							pseudo_legal_moves.push_back(Move(i, i - 7, BLACK_ENPASSANT)):
							pseudo_legal_moves.push_back(Move(i, i - 7));
					}
					if (i % 8 != 0 and ((color[i - 9] == White and board[i - 9]) or i - 9 == enPassantSq)) {
						i - 9 == enPassantSq ?
							pseudo_legal_moves.push_back(Move(i, i - 9, BLACK_ENPASSANT)) :
							pseudo_legal_moves.push_back(Move(i, i - 9));
					}
					if (not board[i - 8]) {
						pseudo_legal_moves.push_back(Move(i, i - 8));
						if (i >= 48 and not board[i - 16]) {
							pseudo_legal_moves.push_back(Move(i, i - 16, BLACK_PAWNTWOSQUARES));
						}
					}
				}
			}
			else
			{
				for (int j = 0; j < offsets[piece]; j++) {
					bool flag = true;
					int n = i;
					while (flag) {
						n = mailbox[mailbox64[n] + offset[piece][j]];
						if (n == -1) break;
						if (board[n] != None) {
							if (color[n] != turn) {
								pseudo_legal_moves.push_back(Move(i, n));
							}
							break;
						}
						pseudo_legal_moves.push_back(Move(i, n));
						if (piece == Knight or piece == King) break;
					}

				}

			}

		}
	
	}
	
	switch (turn)
	{
	case White:
		if (WhiteCastling & 1 and not board[f1] and not board[g1])
			pseudo_legal_moves.push_back(Move(e1, g1, WHITE_KINGSIDE_CASTLE));
		if (WhiteCastling & 2 and not board[d1] and not board[c1] and not board[b1])
			pseudo_legal_moves.push_back(Move(e1, c1, WHITE_QUEENSIDE_CASTLE));
		break;
	case Black:
		if (BlackCastling & 1 and not board[f8] and not board[g8])
			pseudo_legal_moves.push_back(Move(e8, g8, BLACK_KINGSIDE_CASTLE));
		if (BlackCastling & 2 and not board[d8] and not board[c8] and not board[b8])
			pseudo_legal_moves.push_back(Move(e8, c8, BLACK_QUEENSIDE_CASTLE));
		break;
	default:
		break;
	}
	
	
	
	return;
}

void Board::push(Move mv)
{
	move_stack.push_back(mv);

	enPassantSq = a8;

	Piece pc = board[mv.from];
	Color cl = color[mv.from];
	SPECIAL sp = mv.special;
	// if piece doesn't exist, tf is the move doing here lool
	if (not pc) { 
		std::cout << "error void Board::push(Move mv)";
		return;  
	} 

	if (cl == Black) {
		fullMoveCounter++;
	}

	// important for if the special flag was missed for castling
	if (pc == King && (mv.from == e1 or mv.from == e8)) {
		switch (mv.to) {
		case g1:
			sp = WHITE_KINGSIDE_CASTLE;
			break;
		case c1:
			sp = WHITE_QUEENSIDE_CASTLE;
			break;
		case g8:
			sp = BLACK_KINGSIDE_CASTLE;
			break;
		case c8:
			sp = BLACK_QUEENSIDE_CASTLE;
			break;
		default:
			break;
		}
		switch (cl) {
		case White:
			WhiteCastling = 0;
			break;
		case Black:
			BlackCastling = 0;
			break;
		default:
			break;
		}
	}


	
	switch (sp)
	{
	case NOT_SPECIAL:
		clearSquare(mv.from);
		fillSquare(cl, pc, mv.to);
		break;

	case PROMOTION_KNIGHT:
		clearSquare(mv.from);
		fillSquare(cl, Knight, mv.to);
		break;

	case PROMOTION_BISHOP:
		clearSquare(mv.from);
		fillSquare(cl, Bishop, mv.to);
		break;

	case PROMOTION_ROOK:
		clearSquare(mv.from);
		fillSquare(cl, Rook, mv.to);
		break;

	case PROMOTION_QUEEN:
		clearSquare(mv.from);
		fillSquare(cl, Queen, mv.to);
		break;

	case WHITE_KINGSIDE_CASTLE:
		clearSquare(e1);
		clearSquare(h1);
		fillSquare(White, King, g1);
		fillSquare(White, Rook, f1);
		break;

	case WHITE_QUEENSIDE_CASTLE:
		clearSquare(e1);
		clearSquare(a1);
		fillSquare(White, King, c1);
		fillSquare(White, Rook, d1);
		break;

	case BLACK_KINGSIDE_CASTLE:
		clearSquare(e8); 
		clearSquare(h8);
		fillSquare(Black, King, g8);
		fillSquare(Black, Rook, f8);
		break;

	case BLACK_QUEENSIDE_CASTLE:
		clearSquare(e8);
		clearSquare(a8);
		fillSquare(Black, King, c8);
		fillSquare(Black, Rook, d8);
		break;

	case WHITE_ENPASSANT:
		clearSquare(mv.from);
		fillSquare(White, Pawn, mv.to);
		clearSquare(static_cast<Square>(mv.to - 8));
		break;

	case BLACK_ENPASSANT:
		clearSquare(mv.from);
		fillSquare(Black, Pawn, mv.to);
		clearSquare(static_cast<Square>(mv.to + 8));
		break;

	case WHITE_PAWNTWOSQUARES:
		clearSquare(mv.from);
		fillSquare(White, Pawn, mv.to);
		enPassantSq = static_cast<Square>(mv.to - 8);
		break;

	case BLACK_PAWNTWOSQUARES:
		clearSquare(mv.from);
		fillSquare(Black, Pawn, mv.to);
		enPassantSq = static_cast<Square>(mv.to - 8);
		break;

	default:
		break;
	}

	if (turn == White) {
		turn = Black;
	}
	else { turn = White; }
	


}

std::ostream& operator<<(std::ostream& out, const Move& mv)
{
	out << "from: " << SquareNames[mv.from] << "\nto: " << SquareNames[mv.to] << "\nspecial: " << mv.special << "\n";

	return out;
}
