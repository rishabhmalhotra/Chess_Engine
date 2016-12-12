#ifndef __LEVEL2__
#define __LEVEL2__
#include "ai.h"

class Grid;

class Level2: public AI{

    public:
        Level2(Grid *g, bool colour);
        int genNewCoords();
        void makeMove() override;
	      void randomMove();
};

#endif
