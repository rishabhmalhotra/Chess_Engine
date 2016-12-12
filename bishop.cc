#include <iostream>
#include <vector>
#include "piece.h"
#include "bishop.h"
#include "grid.h"

Bishop::Bishop(char type): Piece(type, 3){}

void Bishop::attachAttackRange(Grid *g) {
  legalMovesOfQRB(g, 2);
  legalMovesOfQRB(g, 6);
  legalMovesOfQRB(g, 4);
  legalMovesOfQRB(g, 8);
}

void Bishop::attachLegalMoves(Grid *g) {
  int size = attackRange.size();
  for ( int i = 0; i < size; ++i) {
    int oState = attackRange[i]->getOccupiedState();
    if (oState == 0 or (oState-1 == getColour())) legalMoves.push_back(attackRange[i]);
  }
}
