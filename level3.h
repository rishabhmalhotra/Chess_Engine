#ifndef __LEVEL3__
#define __LEVEL3__
#include "ai.h"

class Grid;

class Level3: public AI{

    public:
        Level3(Grid *g, bool colour);
        int genNewCoords();
        void makeMove() override;
	      void randomMove();
        ~Level3() = default;
};

#endif
