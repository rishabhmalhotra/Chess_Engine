#ifndef __KING_H__
#define __KING_H__
#include <iostream>
#include "piece.h"

class King: public Piece {
    
public:
	King(char type);

	void attachAttackRange(Grid *g) override;
	void attachLegalMoves(Grid *g) override;
};

#endif

