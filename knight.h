#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <iostream>
#include "piece.h"

class Knight: public Piece {
    
public:
	Knight(char type);

	void attachAttackRange(Grid *g) override;
	void attachLegalMoves(Grid *g) override;
};

#endif

