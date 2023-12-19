#include <iostream>
#include "board.h"
#include <random>

// probably where the main loop will be.

int main()
{
    Board board;
    board.resetBoard();

    board.push(Move(e2, e4, WHITE_PAWNTWOSQUARES));
    board.push(Move(e7, e5, BLACK_PAWNTWOSQUARES));
    board.push(Move(g1, f3));
    board.push(Move(b8, c6));
    board.push(Move(f1, c4));
    board.push(Move(f8, c5));
    board.push(Move(e1, g1));

    board.publishFEN();

    

    

    

}