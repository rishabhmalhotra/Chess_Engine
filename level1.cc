#include <iostream>
#include <vector>
#include "level1.h"
#include "ai.h"
#include "grid.h"
#include "cell.h"
#include "piece.h"
#include "queen.h"

Level1::Level1(Grid *g, bool colour): AI(g, colour) {}		// ctor

std::vector<std::vector<int>> Level1::popCell(std::vector<std::vector<int>> vec, int pIndex, int cIndex) {
	vec[pIndex].erase(vec[pIndex].begin() + cIndex);
	if (vec[pIndex].size() <= 1) {vec.erase(vec.begin() + pIndex);}
	return vec;
}

void Level1::generateMove(std::vector<std::vector<int>> vec) {
	int pIndex = genRandIndexInRange(0, vec.size());
	if (vec.size() == 0) throw "no more legal moves";
	int cIndex = genRandIndexInRange(1, vec[pIndex].size()-1);
	Piece *p = myPieces->at(vec[pIndex][0]);
	Cell *c = p->legalMoves[vec[pIndex][cIndex]];// cIndex-1
	int x1 = p->getX();
	int y1 = p->getY();
	int x2 = c->getX();
	int y2 = c->getY();
std::cerr << "Piece is " << p->getType() << ", move from " << x1 << ',' << y1 << "to " << x2 << ',' << y2 << '\n';
	try {
		g->move(x1, y1, x2, y2);
                // check for promotion                                                    
                if (p->getType() == 'P' and y2 == 0) {                                 
                        p->setTakenOut(g->moveCount() -1);                                
                        Piece *newPiece = new Queen('Q');                                 
                        g->place(newPiece, x2, y2);
                        g->updateRecord("Q");
                } else if (p->getType() == 'p' and y2 == 7) {
                        p->setTakenOut(g->moveCount() -1);
                        Piece *newPiece = new Queen('q');
                        g->place(newPiece, x2, y2);
                        g->updateRecord("q");
                }
	} catch (...) {
		// pop off the illegal move
		generateMove(popCell(vec, pIndex, cIndex));
	}
}

void Level1::makeMove() {
// generate the a vector of vectors
	std::vector<std::vector <int>> vec;
	int pSize = myPieces->size();
	for (int i = 0; i < pSize; ++i) {
		std::vector<int> cellIndex;
		cellIndex.push_back(i); // push the index of piece
		int cSize = myPieces->at(i)->legalMoves.size();
		for (int j = 0; j < cSize; ++j) {
			cellIndex.push_back(j);
		}
		if (cellIndex.size() > 1) vec.push_back(cellIndex);
	}
	generateMove(vec);
}
