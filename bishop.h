#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <iostream>
#include "piece.h"

class Bishop: public Piece {

  public:
    Bishop(char type);

    void attachAttackRange(Grid *g) override;
    void attachLegalMoves(Grid *g) override;
};

#endif

