#include <iostream>
#include <vector>
#include "piece.h"
#include "cell.h"
#include "grid.h"

Piece::Piece(char type, int priority): priority{priority}, type{type}, colour{type <= 90}{}

void Piece::setCord(int xCoord, int yCoord) {
	x = xCoord;
	y = yCoord;;
}

int Piece::getX() const { return x; }

int Piece::getY() const { return y; }

char Piece::getType() const { return type; }

//bool Piece::getState() const { return beingCaptured;}
bool Piece::getColour() const { return colour; }

int Piece::getPriority() const { return priority; }

int Piece::getStep() const { return step;}

void Piece::addStep() { ++step; }

void Piece::subStep() { --step; }

int Piece::getTakenOut() const { return takenOut; }

void Piece::setTakenOut(int n) { takenOut = n; }

void Piece::setForward(int n) { forwardTwoTurn = n; }

int Piece::getForward() const { return forwardTwoTurn; }

void Piece::attach(Cell *c) {
	c->alertOn(getColour());
	attackRange.push_back(c);
}

void Piece::legalMovesOfQRB(Grid *g, int dir) {
	if (dir == 1) { // north
        for (int i = y-1; i >= 0; --i) {
            Cell *c = g->getCellAddress(x,i);
	    attach(c);    
            if (c->getOccupiedState() != 0) {
                break;
            }
        }
    } else if (dir == 2) { // north-east
        int i = x+1, j = y-1;
        while (i < 8 and j >= 0) {
            Cell *c = g->getCellAddress(i,j);
	    attach(c);
            if (c->getOccupiedState() != 0) {
                break;
            }
            ++i;
            --j;
        }
    } else if (dir == 3) { // east
        for (int i = x+1; i < 8; ++i) {
            Cell *c = g->getCellAddress(i,y);
            attach(c);
	    if (c->getOccupiedState() != 0) {
                break;
            }
        }
    } else if (dir == 4) { // south-east
        int i = x+1, j = y+1;
        while (i < 8 and j < 8) {
            Cell *c = g->getCellAddress(i,j);
	    attach(c);
            if (c->getOccupiedState() != 0) {
                break;
            }
            ++i;
            ++j;
        }
    } else if (dir == 5) { // south
        for (int i = y+1; i < 8; ++i) {
            Cell *c = g->getCellAddress(x,i);
            attach(c);
	    if (c->getOccupiedState() != 0) {
                break;
            }
        }
    } else if (dir == 6) { // south-west
        int i = x-1, j = y+1;
        while (j < 8 and i >= 0) {
            Cell *c = g->getCellAddress(i,j);
            attach(c);
	    if (c->getOccupiedState() != 0) {
                break;
            }
            --i;
            ++j;
        }
    } else if (dir == 7) { // west
        for (int i = x-1; i >= 0; --i) {
            Cell *c = g->getCellAddress(i,y);
            attach(c);
	    if (c->getOccupiedState() != 0) {
                break;
            }
        }
    } else if (dir == 8) { // north-west
        int i = x-1, j = y-1;
        while (i >= 0 and j >= 0) {
            Cell *c = g->getCellAddress(i,j);
            attach(c);
	    if (c->getOccupiedState() != 0) {
                break;
            }
            --i;
            --j;
        }
    }
}

void Piece::detachMoves() {
	for ( int i = attackRange.size()-1; i >= 0; --i) {
		attackRange[i]->alertOff(getColour());
	}
	attackRange.clear();
	legalMoves.clear();
}

void Piece::reAttach(Grid *g) {
	detachMoves();
	attachAttackRange(g);
	attachLegalMoves(g);
}

bool Piece::moveInRange(int xCoord, int yCoord) {
	int size = legalMoves.size();
	for ( int i = 0; i < size; ++i ) {
		if ( legalMoves[i]->getX() == xCoord and legalMoves[i]->getY() == yCoord ) return true;
	}
	return false;
}

bool Piece::cantMove(Grid *g) {
	int size= legalMoves.size();
	for ( int i = 0; i < size; ++i) {
		if (!g->badMove(getX(), getY(), legalMoves[i]->getX(), legalMoves[i]->getY())) return false;
	}
	return true;
}
