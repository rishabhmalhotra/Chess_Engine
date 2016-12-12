#include <iostream>
#include <vector>
#include "piece.h"
#include "pawn.h"
#include "cell.h"
using namespace std;

Pawn::Pawn(char type): Piece(type, 1){}

bool Pawn::enpassant(int currentTurn, Piece *p) {
  if (p->getType() != 'p' and p->getType() != 'P') return false;
  if (getColour()) {
    if ((getY() == 3 and p->getY() == 3) and p->getType() == 'p' and ((getX() == p->getX()+1) or (getX() == p->getX()-1)) and (currentTurn - p->getForward() <= 1)) {
      return true;
    }
  } else {
    if ((getY() == 4 and p->getY() == 4) and p->getType() == 'P' and ((getX() == p->getX()+1) or (getX() == p->getX()-1)) and (currentTurn - p->getForward() <= 1)) {
      return true;
    }
  }
  return false;
}

void Pawn::attachAttackRange(Grid *g) {
  if (getX()-1 >= 0 and getY() <= 6 and getY() >= 1) {
    if (getColour()) {
      Cell *leftCell = g->getCellAddress(x-1,y-1);
      attach(leftCell);
    } else {
      Cell *leftCell = g->getCellAddress(x-1,y+1);
      attach(leftCell); 
    }
  }
  if (getX()+1 < 8 and getY() <= 6 and getY() >= 1) {
    if (getColour()) {
      Cell *rightCell = g->getCellAddress(x+1,y-1);
      attach(rightCell);
    } else {
      Cell *rightCell = g->getCellAddress(x+1,y+1);
      attach(rightCell);
    }
  }
}

void Pawn::attachLegalMoves(Grid *g) {
  const int xCoord = getX();
  const int yCoord = getY();
  int x = xCoord;                       // mutable copy of x-coord
  int y = yCoord;                       // mutable copy of y-coord
  if (getStep() == 0) {
    if (getColour() and y == 6 and g->getCellAddress(x, y-1)->getOccupiedState() == 0) {
      Cell *forward2 = g->getCellAddress(x,y-2);
      if (forward2->getOccupiedState() == 0) legalMoves.push_back(forward2);
    } else if (!getColour() and y == 1 and g->getCellAddress(x, y+1)->getOccupiedState()==0) {
      Cell *forward2 = g->getCellAddress(x,y+2);
      if (forward2->getOccupiedState() == 0) legalMoves.push_back(forward2);
    }
  }
  // move forward two cells
  if (x-1 > 0) {
    Piece *leftPawn = g->getCellAddress(x-1,y)->returnPiece();
    if (leftPawn) {
      if (enpassant(g->moveCount(), leftPawn)) {
        if (getColour()) legalMoves.push_back(g->getCellAddress(x-1,y-1));
        else legalMoves.push_back(g->getCellAddress(x-1,y+1));
      }
    }
  }
  if (x+1 < 8) {	
    Piece *rightPawn = g->getCellAddress(x+1,y)->returnPiece();
    if (rightPawn) {
      if (enpassant(g->moveCount(), rightPawn)) {
        if (getColour()) legalMoves.push_back(g->getCellAddress(x+1,y-1));
        else legalMoves.push_back(g->getCellAddress(x+1,y+1));
      }
    }
  }
  // en passant
  if (getColour() and y > 0) {// white
    Cell *forward1 = g->getCellAddress(x,y-1);
    if (forward1->getOccupiedState() == 0) legalMoves.push_back(forward1);
    if (x >= 1) {
      Cell *leftCell = g->getCellAddress(x-1,y-1); 
      if (leftCell->getOccupiedState() == 2) legalMoves.push_back(leftCell);
    }
    if (x < 7) {
      Cell *rightCell = g->getCellAddress(x+1,y-1);
      if (rightCell->getOccupiedState() == 2 ) legalMoves.push_back(rightCell);
    }
  } else if (!getColour() and y < 7) { // black
    Cell *forward1 = g->getCellAddress(x,y+1);
    if (forward1->getOccupiedState() == 0) legalMoves.push_back(forward1);
    if (x >= 1) {
      Cell *leftCell = g->getCellAddress(x-1,y+1);
      if (leftCell->getOccupiedState() == 1) legalMoves.push_back(leftCell);
    }
    if (x < 7) {
      Cell *rightCell = g->getCellAddress(x+1,y+1);
      if (rightCell->getOccupiedState() == 1) legalMoves.push_back(rightCell);
    }
  }

}
