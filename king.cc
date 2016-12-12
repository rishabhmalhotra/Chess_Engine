#include <iostream>
#include <vector>
#include "piece.h"
#include "king.h"
#include "grid.h"

King::King(char type): Piece(type, 100){}

void King::attachAttackRange(Grid *g) {
	for (int i = x-1; i <= x+1; ++i) {
		if (i >= 0 and i < 8) {
			for (int j = y-1; j <=y+1; ++j) {
				if (j >= 0 and j < 8 and !(i == x and j == y)) {
					attach(g->getCellAddress(i, j));
				}
			}
		}
	}
}
 
void King::attachLegalMoves(Grid *g) {
	int size = attackRange.size();
	for (int i = 0; i < size; ++i) {
		int oState = attackRange[i]->getOccupiedState();
		bool tState = attackRange[i]->threatenState(!colour) == 0;
                if ( tState and (oState == 0 or (oState-1 == getColour()))) legalMoves.push_back(attackRange[i]);
	}
	// check if king is in check and the safety of cell (x, y)
	if (x == 4) {
	bool c1 = g->getCellAddress(1, y)->threatenState(!colour) == 0;
        bool c2 = g->getCellAddress(2, y)->threatenState(!colour) == 0;
        bool c3 = g->getCellAddress(3, y)->threatenState(!colour) == 0;
        bool c4 = g->getCellAddress(4, y)->threatenState(!colour) == 0;
        bool c5 = g->getCellAddress(5, y)->threatenState(!colour) == 0;
        bool c6 = g->getCellAddress(6, y)->threatenState(!colour) == 0;
	bool o1 = g->getCellAddress(1, y)->getOccupiedState() == 0;
        bool o2 = g->getCellAddress(2, y)->getOccupiedState() == 0;
        bool o3 = g->getCellAddress(3, y)->getOccupiedState() == 0;
        bool o5 = g->getCellAddress(5, y)->getOccupiedState() == 0;
        bool o6 = g->getCellAddress(6, y)->getOccupiedState() == 0;

	if (getStep() == 0) {// for castling, note that castling through or out of check is prohibited
		Piece *rookLeft = (g->getCellAddress(x-4,y))->returnPiece();
		if ( c1 and c2 and c3 and c4 and o1 and o2 and o3 and rookLeft and rookLeft->getStep() == 0 
		and ((rookLeft->getType()=='R' and getType()=='K') or ( rookLeft->getType() == 'r' and getType() == 'k')) ) {
			legalMoves.push_back(g->getCellAddress(x-2, y));
		}
		Piece *rookRight = (g->getCellAddress(x+3,y))->returnPiece(); 
		if ( c4 and c5 and c6 and o5 and o6 and rookRight and rookRight->getStep() == 0 
		and ((rookRight->getType() == 'R' and getType() == 'K') or ( rookRight->getType() == 'r' and getType() == 'k')) ) {
			legalMoves.push_back(g->getCellAddress(x+2, y));
		}
	}}
}
