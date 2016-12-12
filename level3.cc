#include "level3.h"
#include "ai.h"
#include "grid.h"
#include "piece.h"
#include <stdlib.h>
#include <vector>
#include "queen.h"
using namespace std;

Level3::Level3(Grid* g, bool colour): AI(g, colour) {} 	// ctor

void Level3::randomMove() {
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
     p->setTakenOut(g->moveCount() -1);
     Piece *newPiece = new Queen('Q');
     g->place(newPiece, cellX, cellY);
     g->updateRecord("Q");
     g->reAttachAll();
    } else if (p->getType() == 'p' and cellY == 7) {
     p->setTakenOut(g->moveCount() -1);
     Piece *newPiece = new Queen('q');
     g->place(newPiece, cellX, cellY);
     g->updateRecord("q");
     g->reAttachAll();
    }
   }
   catch (const char* msg) {
    randomMove();
   }
}


void Level3::makeMove() {

  int colourInt1, colourInt2 = 0;		// AI's opponent's colour

  if (colour == 0) {		// AI's colour
   colourInt1 = 1;
   colourInt2 = 2;
  } else {
   colourInt1 = 2;
   colourInt2 = 1;
  }

  bool found = false;                                           // did we find anythying to move
  bool breakOutOfMainLoop = false;
  bool breakOutOfForLoop = false;

  vector <Piece*> *opponentPieces = nullptr;

  bool savedMyPiece = false;

  // select the elements of the opponent's Pieces one-by-one and for each, check if any of its legalMoves has any myPiece within attack vicinity. If I find something, move myPiece to safety.

  unsigned int k = 0;

  if (colourInt2 == 1) {
   opponentPieces = &(g->blackPieces);
  } else if (colourInt2 == 2) {
   opponentPieces = &(g->whitePieces);
  }

  while (k < opponentPieces->size()) {
   if (breakOutOfMainLoop == true) {
    break;
   }
   Piece *opponentPiece = (*opponentPieces)[k];
   for (unsigned int j = 0; j < (opponentPiece->attackRange).size(); ++j) {
    if ((j == opponentPiece->attackRange.size()-1) && ((opponentPiece->attackRange[j])->getOccupiedState() != colourInt2)) {
     if (k == opponentPieces->size()-1) {
      breakOutOfMainLoop = true;
     }
     break;
    }
    if (opponentPiece->attackRange[j]->getOccupiedState() == colourInt2) {		// AI under risk from opponent
     Cell *c = opponentPiece->attackRange[j];           // Cell on which my threatened piece is
     Piece *myPieceOnCell = c->returnPiece();					// My (AI's) piece under threat
     
     //AI piece under threat
     
     found = true;
     // If my threatened piece can attack and capture the predator (opponent's piece that threatens me)
     for (unsigned int d=0; d < (myPieceOnCell->attackRange).size(); ++d) {
       if (((myPieceOnCell->attackRange[d])->getX() == opponentPiece->getX()) && 
           ((myPieceOnCell->attackRange[d])->getY() == opponentPiece->getY())) {
         
         //trying to take on predator
         
         g->move(c->getX(), c->getY(), opponentPiece->getX(), opponentPiece->getY());
         //successfully destroyed predator
         
         if (myPieceOnCell->getType() == 'P' and opponentPiece->getY() == 0) {
          myPieceOnCell->setTakenOut(g->moveCount() -1);
          Piece *newPiece = new Queen('Q');
          g->place(newPiece, myPieceOnCell->getX(), myPieceOnCell->getY());
          g->updateRecord("Q");
          g->reAttachAll();
         } else if (myPieceOnCell->getType() == 'p' and opponentPiece->getY() == 7) {
          myPieceOnCell->setTakenOut(g->moveCount() -1);
          Piece *newPiece = new Queen('q');
          g->place(newPiece, myPieceOnCell->getX(), myPieceOnCell->getY());
          g->updateRecord("q");
          g->reAttachAll();
         }
         breakOutOfForLoop = true;
         breakOutOfMainLoop = true;
         savedMyPiece = true;
         break;
       }
     }
     if (breakOutOfForLoop == true) {
       break;
     }
     randomMove();
     savedMyPiece = true;
     try {
       int stopEnough = 0;
       bool broken = 0;
      for (unsigned int h = 0; h < (opponentPiece->attackRange).size(); ++h) {
       if ((myPieceOnCell->getX() == ((opponentPiece->attackRange[h])->getX())) && (myPieceOnCell->getY() == 
             ((opponentPiece->attackRange[h])->getY()))) {
        // random move wasn't good enough; still under threat; undoing move
        
        g->undo();
        // again trying another randomMove()
        
        randomMove();
        breakOutOfMainLoop = true;
	      h = 0;
        ++stopEnough;
        if (stopEnough >= 30) {
         break;
         broken = 1;
        }
       }
      }
      if (broken == 1) {
       breakOutOfMainLoop = true;
       break;
      }
     }
     catch (...) {
      breakOutOfMainLoop = true;
      break;
     }
    }
   }
   ++k;
  }
  if (found == 0) {
   randomMove();
   savedMyPiece = true;
  }
  
  breakOutOfMainLoop = false;
  found = 0;

  if (savedMyPiece == false) {
   
   //select the elements of the myPieces vector one-by-one and for each, check if any of its legalMoves has an opponent piece that can be captured.
  
   unsigned int i = 0;

   while (i < myPieces->size()) {
    if (breakOutOfMainLoop == true) {
     break;
    }
    Piece *p = (*myPieces)[i];                          				// myPieces is set in the AI superclass
    for (unsigned int j = 0; j < (p->legalMoves).size(); ++j) {
     if ((j == p->legalMoves.size()-1) && ((p->legalMoves[j])->getOccupiedState() != colourInt1)) {
      if (i == myPieces->size()-1) {
       breakOutOfMainLoop = true;
      }
      break;
     }
     if (p->legalMoves[j]->getOccupiedState() == colourInt1) {
     Cell *c = p->legalMoves[j];
     int pieceX = p->getX();
     int pieceY = p->getY();
     int cellX = c->getX();
     int cellY = c->getY();
     found = true;
     try {
      g->move(pieceX, pieceY, cellX, cellY);
      if (p->getType() == 'P' and cellY == 0) {                 // for replacing the pawn at the end
       p->setTakenOut(g->moveCount() -1);
       Piece *newPiece = new Queen('Q');
       g->place(newPiece, cellX, cellY);
       g->updateRecord("Q");
       g->reAttachAll();
      } else if (p->getType() == 'p' and cellY == 7) {
       p->setTakenOut(g->moveCount() -1);
       Piece *newPiece = new Queen('q');
       g->place(newPiece, cellX, cellY);
       g->updateRecord("q");
       g->reAttachAll();
      }
      breakOutOfMainLoop = true;                                  // break out of outer loop
      break;                                                      // break out of inner loop
     }
     catch (...) {
      if (j == p->legalMoves.size()-1) {
       break;                                                     // get out of this inner loop
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
}
