//The AI Class
#ifndef __AI__
#define __AI__
#include <vector>
#include "grid.h"

class Piece;

class AI{
    protected: 
        Grid *g;
        bool colour;
	      std::vector<Piece *> *myPieces;
    public:  
	      AI(Grid *g, bool colour);
	      virtual ~AI();
        virtual void makeMove() = 0;
	      int genRandIndexInRange(int low, int high);
	      Piece* getRandPiece();
};
#endif
