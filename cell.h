#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <vector>
#include "observer.h"
class Piece;

class Cell: public Observer {
  int x, y; // x, y coordinate
  Piece *myPiece = nullptr;
  int occupied = 0; //0 means empty, 1 means occupied by white, 2 means occupied by black
  int threatenByWhite = 0; // 0 means it can be reached by 0 white pieces
  int threatenByBlack = 0;

  public:
  Cell(); 
  void clean();
  void setCoord(int xCoord, int yCoord); // set x, y coordinates

  int getX() const; // returns x coordinate.
  int getY() const; // returns y coordinate.
  int getOccupiedState() const; // returns 0, 1 or 2.
  int whiteThreatenState() const;
  int blackThreatenState() const;
  int threatenState(bool colour) const;
  Piece *returnPiece() const;

  void alertOn(bool colour); // alert on when it can be attacked
  void alertOff(bool colour); // alert off when the piece leave


  void comeNotify(Piece *p, bool colour);// override; // get notified when a piece moves on the cell.
  void leaveNotify(int x, int y);// override; // get notified when a piece leaves the cell.

};

#endif
