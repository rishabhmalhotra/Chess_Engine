#include <iostream>
#include <vector>
#include "piece.h"
#include "rook.h"
#include "grid.h"

Rook::Rook(char type): Piece(type, 5){}

void Rook::attachAttackRange(Grid *g) {
    legalMovesOfQRB(g, 1);
    legalMovesOfQRB(g, 5);
    legalMovesOfQRB(g, 3);
    legalMovesOfQRB(g, 7);
}

void Rook::attachLegalMoves(Grid *g) {
	int size = attackRange.size();
	for ( int i = 0; i < size; ++i) {
		int oState = attackRange[i]->getOccupiedState();
		if (oState == 0 or (oState-1 == getColour())) legalMoves.push_back(attackRange[i]);
	}
}
