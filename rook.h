#ifndef __ROOK_H__
#define __ROOK_H__
#include <iostream>
#include "piece.h"

class Rook: public Piece {
    
public:
	Rook(char type);

	void attachAttackRange(Grid *g);
	void attachLegalMoves(Grid *g);
};

#endif

