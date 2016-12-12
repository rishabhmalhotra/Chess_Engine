#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "ai.h"
#include "grid.h"
#include "piece.h"

AI::AI(Grid* g, bool colour): g{g}, colour{g->getTurn()} {
    if (colour) {
        myPieces = &g->whitePieces;		// func in main
    } else {
        myPieces = &g->blackPieces;		// func in main
    }
}

AI::~AI() {g = nullptr; myPieces = nullptr;}

int AI::genRandIndexInRange(int low, int high) {
    srand(time(NULL));
    //generate a random index number from
    //low to size
    int randomIndex = rand() % high + low;
    return randomIndex;
}

Piece* AI::getRandPiece() {
  std::vector<int> piecesCanMove;
	//int size = vPieces.size();
    for (unsigned int i = 0; i < myPieces->size(); ++i) {
        if (myPieces->at(i)->legalMoves.size() != 0) {piecesCanMove.push_back(i);}
    }
    //choose a spot on the grid which is 
    //a piece of the same colour as my AI
    //
    //then check the valid moves for the piece
    //and choose one at random
    int ranIndex = genRandIndexInRange(0, piecesCanMove.size());
    return myPieces->at(piecesCanMove[ranIndex]);
}
