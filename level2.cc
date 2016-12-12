#include "level2.h"
#include "ai.h"
#include "grid.h"
#include "piece.h"
#include <stdlib.h>
#include "queen.h"
using namespace std;

Level2::Level2(Grid* g, bool colour): AI(g, colour) {} // ctor


void Level2::randomMove() {
   // random move just like Level1
 
   //choose a random piece
   Piece* p = getRandPiece();
   int size = p->legalMoves.size();
   
   //random legal position to move to
   Cell* c = p->legalMoves[genRandIndexInRange(0, size)];
   
   //get all necessary coordinates
   int pieceX = p->getX();
   int pieceY = p->getY();
   int cellX = c->getX();
   int cellY = c->getY();
   
   //move the piece
   try {
    g->move(pieceX, pieceY, cellX, cellY);
    if (p->getType() == 'P' and cellY == 0) {
     p->setTakenOut(g->moveCount() - 1);
     Piece *newPiece = new Queen('Q');
     g->place(newPiece, cellX, cellY);
     g->updateRecord("Q");
    } else if (p->getType() == 'p' and cellY == 7) {
     p->setTakenOut(g->moveCount() -1);
     Piece *newPiece = new Queen('q');
     g->place(newPiece, cellX, cellY);
     g->updateRecord("q");
    }
   }
   catch (const char* msg) {
    randomMove();
   }
}


void Level2::makeMove() {
    //select the elements of the myPieces vector one-by-one and for each, check if any of it's legalMoves has an opponent piece that can be captured.
    int colourInt = 0;
    
    if (colour == 0) 
    {
        colourInt = 1;
    } 
    else 
    {
        colourInt = 2;
    }
    
    bool found = false;	// did we find anythying to move
    bool breakOutOfMainLoop = false;
    unsigned int i = 0;
    
    while (i < myPieces->size()) {
        if (breakOutOfMainLoop == true) {
            break;
        }
        Piece *p = (*myPieces)[i];				                            // myPieces is set in the AI superclass
        for (unsigned int j = 0; j < (p->legalMoves).size(); ++j) {
            if ((j == p->legalMoves.size()-1) && ((p->legalMoves[j])->getOccupiedState() != colourInt)) {
                if (i == myPieces->size()-1) {
                    breakOutOfMainLoop = true;				                // break out of outer loop
                }
                break;							                                  // break out of inner loop
            }
            if (p->legalMoves[j]->getOccupiedState() == colourInt) {
                
                Cell *c = p->legalMoves[j];
                int pieceX = p->getX();
                int pieceY = p->getY();
                int cellX = c->getX();
                int cellY = c->getY();
                
                found = true;
                
                try {
                    g->move(pieceX, pieceY, cellX, cellY);
                    if (p->getType() == 'P' and cellY == 0) {
                     p->setTakenOut(g->moveCount() - 1);
                     Piece *newPiece = new Queen('Q');
                     g->place(newPiece, cellX, cellY);
                     g->updateRecord("Q");
                    } else if (p->getType() == 'p' and cellY == 7) {
                     p->setTakenOut(g->moveCount() -1);
                     Piece *newPiece = new Queen('q');
                     g->place(newPiece, cellX, cellY);
                     g->updateRecord("q");
                    }
                    breakOutOfMainLoop = true;					// break out of outer loop
                    break;								// break out of inner loop
                }
                catch (...) {
                    if (j == p->legalMoves.size()-1) {
                        break;							// get out of this inner loop
                    } else {
                        continue;
                    }
                } 
            }
        }
        ++i;
    }

    if (found == 0) {
     randomMove();
    }
}
