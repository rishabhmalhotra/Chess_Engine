#include <iostream>
#include <vector>
#include "piece.h"
#include "knight.h"
#include "grid.h"

Knight::Knight(char type): Piece(type, 2){}
    
void Knight::attachAttackRange(Grid *g) {
   const int xCoord = getX();
   const int yCoord = getY();
   int x = xCoord;                             // mutable instance of x-coord
   int y = yCoord;                             // mutable instance of y-coord

	if (x+2 >= 0 and x+2 < 8 and y+1 >= 0 and y+1 < 8) attach(g->getCellAddress(x+2,y+1));
	if (x+2 >= 0 and x+2 < 8 and y-1 >= 0 and y-1 < 8) attach(g->getCellAddress(x+2,y-1));
	if (x-2 >= 0 and x-2 < 8 and y+1 >= 0 and y+1 < 8) attach(g->getCellAddress(x-2,y+1));
	if (x-2 >= 0 and x-2 < 8 and y-1 >= 0 and y-1 < 8) attach(g->getCellAddress(x-2,y-1));
	if (x-1 >= 0 and x-1 < 8 and y+2 >= 0 and y+2 < 8) attach(g->getCellAddress(x-1,y+2));
	if (x-1 >= 0 and x-1 < 8 and y-2 >= 0 and y-2 < 8) attach(g->getCellAddress(x-1,y-2));
	if (x+1 >= 0 and x+1 < 8 and y+2 >= 0 and y+2 < 8) attach(g->getCellAddress(x+1,y+2));
	if (x+1 >= 0 and x+1 < 8 and y-2 >= 0 and y-2 < 8) attach(g->getCellAddress(x+1,y-2));
}

void Knight::attachLegalMoves(Grid *g) {
	int size = attackRange.size();
	for ( int i = 0; i < size; ++i) {
		int oState = attackRange[i]->getOccupiedState();
		if (oState == 0 or (oState-1 == getColour())) legalMoves.push_back(attackRange[i]);
	}
}
