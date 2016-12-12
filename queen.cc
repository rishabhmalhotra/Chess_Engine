#include <iostream>
#include <vector>
#include "piece.h"
#include "queen.h"
#include "grid.h"

Queen::Queen(char type): Piece(type, 10){}
 
void Queen::attachAttackRange(Grid *g) {
    legalMovesOfQRB(g, 5);
    legalMovesOfQRB(g, 1);
    legalMovesOfQRB(g, 3);
    legalMovesOfQRB(g, 7);
    legalMovesOfQRB(g, 2);
    legalMovesOfQRB(g, 6);
    legalMovesOfQRB(g, 4);
    legalMovesOfQRB(g, 8);
}

void Queen::attachLegalMoves(Grid *g) {
	int size = attackRange.size();
	for ( int i = 0; i < size; ++i) {
		int oState = attackRange[i]->getOccupiedState();
		if (oState == 0 or (oState-1 == getColour())) legalMoves.push_back(attackRange[i]);
	}
}
