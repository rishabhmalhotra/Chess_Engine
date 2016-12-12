#include <iostream>
#include <vector>
#include "cell.h"
class Piece;

Cell::Cell(){}
void Cell::setCoord(int xCoord, int yCoord) {
  x = xCoord;
  y = yCoord;
}
void Cell::clean() {
  myPiece = nullptr;
  occupied = 0;
  threatenByWhite = 0;
  threatenByBlack = 0;
}

int Cell::getX() const { return x; } 
int Cell::getY() const { return y; }
int Cell::getOccupiedState() const { return occupied; }
int Cell::whiteThreatenState() const {return threatenByWhite;}
int Cell::blackThreatenState() const {return threatenByBlack;}
int Cell::threatenState(bool colour) const {
  if (colour) {
    return threatenByWhite;
  } else {
    return threatenByBlack;
  }
}

Piece* Cell::returnPiece() const { return myPiece; }

void Cell::alertOn(bool colour) {
  if (colour) {
    ++threatenByWhite; 
  } else {
    ++threatenByBlack;
  }
}

void Cell::alertOff(bool colour) {
  if (colour) {
    --threatenByWhite;
  } else {
    --threatenByBlack;
  }    
}

void Cell::comeNotify(Piece *p, bool colour) {
  myPiece = p;
  if (colour) occupied = 1;
  else occupied = 2;
}

void Cell::leaveNotify(int x, int y) {
  myPiece = nullptr;
  occupied = 0;
}

