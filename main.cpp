#include <iostream>
#include "board.h"


int main()
{
    Board board;
    board.loadFromFEN("rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
    board.loadFromFEN("3q3r/1p2kpp1/p2R1N1p/8/1Q6/5P1P/PP3P2/4K2R b Qk - 0 21");
    board.publishFEN();
    Square sq = f2;
    std::cout << "piece at " << SquareNames[sq] << " is " << board.pieceAt(sq);
}