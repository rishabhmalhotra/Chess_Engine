#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <iostream>
#include "piece.h"

class Queen: public Piece {
    
public:
	Queen(char type);
  
	void attachAttackRange (Grid *g) override;
	void attachLegalMoves(Grid *g) override;
};

#endif

