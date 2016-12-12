#ifndef __LEVEL1__
#define __LEVEL1__
#include "ai.h"

class Grid;

class Level1: public AI{

    public:
        Level1(Grid* g, bool colour);			// ctor
	      std::vector<std::vector<int>> popCell(std::vector<std::vector<int>> vec, int pIndex, int cIndex);
	      void generateMove(std::vector<std::vector<int>> vec);
        void makeMove() override;				
};

#endif
