#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <vector>
#include "grid.h"
class Cell;
class Grid;

class Piece {   
	bool beingCaptured = false;
	int step = 0;
	int priority; //for AI.
	char type; // p, r, n, b, q, k.
	int forwardTwoTurn=0;//only available for pawns.
	int takenOut = 0;
	
protected:
	std::vector<Cell *> attackRange;
	std::vector<Cell *> legalMoves;
	int x, y;
	bool colour;
	
public:
	Piece(char type, int priority);
	virtual ~Piece()=default; // remember to cut all the connections with player, cell.
	void setCord(int xCoord, int yCoord);
	int getX() const; // Returns the value of r.
	int getY() const; // Returns the value of c.
	char getType() const;
	bool getBeingCaptured() const; // being captured?
	bool getColour() const;
	int getPriority() const;
	int getStep() const;
	void addStep();
	void subStep();
	void setForward(int n);
        int getForward() const;
	int getTakenOut() const;
	void setTakenOut(int n);

	void attach(Cell *c);
	void legalMovesOfQRB(Grid *g, int dir); // direction can be 1 to 8.
	virtual void attachAttackRange(Grid *g) = 0;
	virtual void attachLegalMoves(Grid *g) = 0; // returns an array of possible moves, does not consider blocking stuff.
	void detachMoves();
	void reAttach(Grid *g);	
	bool moveInRange(int xCoord, int yCoord);
	bool cantMove(Grid *g);
	friend class AI;
	friend class Level1;
	friend class Level2;
	friend class Level3;
	// friend class Level4;
};

#endif

