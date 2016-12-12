#ifndef __PAWN_H__
#define __PAWN_H__
#include <iostream>
#include <vector>
#include "piece.h"

class Pawn: public Piece {

public:
	Pawn(char type);

	bool enpassant(int currentTurn, Piece *p);
	void attachAttackRange(Grid *g) override;
	void attachLegalMoves(Grid *g) override;


};

#endif
