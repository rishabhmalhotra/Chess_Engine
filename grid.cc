#include <iostream>
#include <string>
#include "grid.h"
#include "piece.h"
#include "pawn.h"
using namespace std;

Grid::Grid(): whiteWins{0}, blackWins{0} {
	for ( int i = 0; i < 8; ++i ) { // setup first then attach observers
		std::vector<Cell> Row;
		for ( int j = 0; j < 8; ++j ) {
			Cell ij;
			ij.setCoord(j, i);
			Row.push_back(ij);				
		}
		theGrid.push_back(Row);
	}
	td = new TextDisplay();
}

Grid::~Grid(){
	delete td;
	for (unsigned int i = 0; i < whitePieces.size(); ++i) {delete whitePieces[i];}
	whitePieces.clear();
	for (unsigned int i = 0; i < blackPieces.size(); ++i) {delete blackPieces[i];}
	blackPieces.clear();
	for (unsigned int i = 0; i < whiteGarbageCollector.size(); ++i) {delete whiteGarbageCollector[i];}
	whiteGarbageCollector.clear();
	for (unsigned int i = 0; i <  blackGarbageCollector.size(); ++i) {delete blackGarbageCollector[i];}
	blackGarbageCollector.clear();
}

void Grid::clean() {
	totalMoveCount = 0;
	whiteTurn = true;
	running = false;
	td->clean();
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			theGrid[i][j].clean();
		}
	}
	for (unsigned int i = 0; i < whitePieces.size(); ++i) {delete whitePieces[i];}
        whitePieces.clear();
        for (unsigned int i = 0; i < blackPieces.size(); ++i) {delete blackPieces[i];}
        blackPieces.clear();
        for (unsigned int i = 0; i < whiteGarbageCollector.size(); ++i) {delete whiteGarbageCollector[i];}
        whiteGarbageCollector.clear();
        for (unsigned int i = 0; i <  blackGarbageCollector.size(); ++i) {delete blackGarbageCollector[i];}
        blackGarbageCollector.clear();
	record.clear();
} 

void Grid::updateRecord(string s) {
	if (record.back().length() == 4) {record.back() += (" " + s);}
	if (record.back().length() == 5) {record.back() += s;}
}

void Grid::startRunning() {running = true;}
void Grid::stopRunning() {running = false;}

void Grid::resign() {
	if (whiteTurn) ++blackWins;
	else ++whiteWins;	
}

bool Grid::getRunningState() const { return running; }
bool Grid::getTurn() const {return whiteTurn;}
float Grid::getWins(bool c) const {if (c) return whiteWins; else return blackWins;}
Cell *Grid::getCellAddress(int x, int y) {return &theGrid[y][x];}

int Grid::moveCount() const { return totalMoveCount; }

void Grid::setKingPos(bool c, int x, int y) {
	if (c) {wkx = x; wky = y;}
	else {bkx = x; bky = y;}
}

bool Grid::safeCheck(bool c) {
    if (c) {
        return theGrid[wky][wkx].blackThreatenState() == 0;
    } else {
	return theGrid[bky][bkx].whiteThreatenState() == 0;
    }
}

void addHelp(Piece *p, std::vector<Piece *> &v) {
	int size = v.size();
	for (int i = 0; i < size; ++i) {
		if (p->getPriority() <= v[i]->getPriority()) {	// pawn toking 
			v.insert(v.begin()+i, p);
			return;
		}
	}
	v.push_back(p);
}

void Grid::addToVector(Piece* p, int which) {
	if (which == 1) {
		addHelp(p, whitePieces);
	} else if (which == 2) {
		addHelp(p, blackPieces);
	} else if (which == 3) {
		addHelp(p, whiteGarbageCollector);
	} else if (which == 4) {
		addHelp(p, blackGarbageCollector);
	}
}

void Grid::removeFromVector(int x, int y, int which) {
	if (which == 1) {
		int size = whitePieces.size();
		for ( int i = 0; i < size; ++i ) {
			if (whitePieces[i]->getX() == x and whitePieces[i]->getY() == y and (whitePieces[i]->getTakenOut() == totalMoveCount or whitePieces[i]->getTakenOut()+1 ==totalMoveCount)) {
				whitePieces[i] = nullptr;
				whitePieces.erase(whitePieces.begin()+i);
			}
		}
	} else if (which == 2) {
                int size = blackPieces.size();
                for ( int i = 0; i < size; ++i ) {
                        if (blackPieces[i]->getX() == x and blackPieces[i]->getY() == y and (blackPieces[i]->getTakenOut() == totalMoveCount or blackPieces[i]->getTakenOut()+1 ==totalMoveCount)) {
				blackPieces[i] = nullptr;
				blackPieces.erase(blackPieces.begin()+i);
			}
                }
        } else if (which == 3) {
		for (unsigned int i = 0; i < whiteGarbageCollector.size(); ++i ) {
                        if (whiteGarbageCollector[i]->getX() == x and whiteGarbageCollector[i]->getY() == y and (whiteGarbageCollector[i]->getTakenOut() == totalMoveCount or whiteGarbageCollector[i]->getTakenOut()+1 ==totalMoveCount)) {
				whiteGarbageCollector[i] = nullptr;
				whiteGarbageCollector.erase(whiteGarbageCollector.begin()+i);
                	}
		}
        } else if (which == 4) {
                for (unsigned int i = 0; i < blackGarbageCollector.size(); ++i ) {
                        if (blackGarbageCollector[i]->getX() == x and blackGarbageCollector[i]->getY() == y and (blackGarbageCollector[i]->getTakenOut() == totalMoveCount or blackGarbageCollector[i]->getTakenOut()+1 ==totalMoveCount)) {
				blackGarbageCollector[i] = nullptr;
				blackGarbageCollector.erase(blackGarbageCollector.begin()+i);
			}
                }
        }
}

void Grid::reAttachAll() {
	int whiteSize = whitePieces.size();
	int blackSize = blackPieces.size();
	for (int i = 0; i < whiteSize; ++i) {whitePieces[i]->reAttach(this);}
	for (int i = 0; i < blackSize; ++i) {blackPieces[i]->reAttach(this);}
}

void Grid::removePiece(int x, int y) { // you're ensured that (x,y) is not empty.
	theGrid[y][x].returnPiece()->detachMoves();
	theGrid[y][x].leaveNotify(x, y); 
}

void Grid::placePiece(Piece *p, int x, int y) { // for setup
	if (theGrid[y][x].getOccupiedState() != 0) { 
        	removePiece(x, y); 
 	}
	p->setCord(x, y);
	theGrid[y][x].comeNotify(p, p->getColour());
	p->attachAttackRange(this);
	p->attachLegalMoves(this);
	if (p->getType() == 'K') setKingPos(true, x, y);
	if (p->getType() == 'k') setKingPos(false, x, y);
}

void Grid::remove(int x, int y) {
	if (theGrid[y][x].getOccupiedState()!= 0) {
		Piece *temp = theGrid[y][x].returnPiece();
		theGrid[y][x].leaveNotify(x, y);
		td->leaveNotify(x, y);
		temp->setTakenOut(totalMoveCount);
                if (temp->getColour()) {
			removeFromVector(x, y, 1);
                        addToVector(temp, 3);
                } else {
			removeFromVector(x, y, 2);
                        addToVector(temp, 4);
                }
		temp->detachMoves();
	} else {
		throw "No piece on this cell.";
	}
}

void Grid::place(Piece *p, int x, int y) {
	if ((p->getType() == 'P' or p->getType() == 'p') and (y == 0 or y == 7)) throw "Pawn cannot be placed on the first or last row";
	int oState = theGrid[y][x].getOccupiedState();
	if (oState != 0) {remove(x, y);}
	placePiece(p, x, y);
	td->comeNotify(p, p->getColour());
	p->setTakenOut(0);
	if (p->getColour()) addToVector(p, 1);
	else addToVector(p, 2);
}

void Grid::move(int x1, int y1, int x2, int y2) {
	Piece *p1 = theGrid[y1][x1].returnPiece();
  Piece *p2 = theGrid[y2][x2].returnPiece();
	if (p1 == nullptr) throw "No piece on this cell.";
	if (!p1->moveInRange(x2, y2)) throw "Invalid move.";
	std::string tempRecord;
	tempRecord += (x1 + '0');tempRecord += (y1 + '0');tempRecord += (x2 + '0');tempRecord += (y2 + '0');
	removePiece(x1, y1);
	bool safe = safeCheck(p1->getColour());
	if (p2) {
		remove(x2, y2);
	}
	placePiece(p1, x2, y2);
	// now check for castling.
	if (p1->getType() == 'K' or p1->getType() == 'k') {
		if (x1 == 4 and x2 == 2) {
			Piece *leftRook = theGrid[y1][0].returnPiece();
			removePiece(0, y1);
			placePiece(leftRook, 3, y1);
			td->leaveNotify(0, y1);
			td->comeNotify(leftRook, leftRook->getColour());
		} else if (x1 == 4 and x2 == 6) {
			Piece *rightRook = theGrid[y1][7].returnPiece();
                        removePiece(7, y1);
                        placePiece(rightRook, 5, y1);
			td->leaveNotify(7, y1);
                        td->comeNotify(rightRook, rightRook->getColour());
		}
	}
	// now check for en passant
	Piece *p3 = nullptr;
	if ((p1->getType() == 'P' or p1->getType() == 'p') and (x1 != x2) and !p2) { // en passant move
		p3 = theGrid[y1][x2].returnPiece();
		remove(x2,y1);
		reAttachAll();
	}
	reAttachAll();
	if (safeCheck(p1->getColour())) { // safe move
		if (p1->getType() == 'P' and p1->getStep() == 0 and y1 == 6 and y2 == 4) {
			if (x1 - 1 >= 0 and theGrid[4][x2-1].getOccupiedState() == 2) {
				Piece *leftPawn = theGrid[4][x2-1].returnPiece();
				if (leftPawn->getType() == 'p') p1->setForward(totalMoveCount);
			}
			if (x1 + 1 < 8 and theGrid[4][x2+1].getOccupiedState() == 2) {
				Piece *rightPawn = theGrid[4][x2+1].returnPiece();
				if (rightPawn->getType() == 'p') p1->setForward(totalMoveCount);
			}
                }
		if (p1->getType() == 'p' and p1->getStep() == 0 and y1 == 1 and y2 == 3) {
                        if (x1 - 1 >= 0 and theGrid[3][x2-1].getOccupiedState() == 1) {
                                Piece *leftPawn = getCellAddress(x2-1, 3)->returnPiece();
                                if (leftPawn->getType() == 'P') p1->setForward(totalMoveCount);
                        }
                        if (x1 + 1 < 8 and theGrid[3][x2+1].getOccupiedState() == 1) {
                                Piece *rightPawn = getCellAddress(x2+1, 3)->returnPiece();
                                if (rightPawn->getType() == 'P') p1->setForward(totalMoveCount);
                        }
                } // notify enemy's pawns
		if (p2) { p2->setTakenOut(totalMoveCount); tempRecord += 'e';}
		if (p3) { p3->setTakenOut(totalMoveCount); tempRecord += 'e';td->leaveNotify(x2, y1); }
		td->leaveNotify(x1, y1);
        	td->comeNotify(p1, p1->getColour());
		p1->addStep();
		++totalMoveCount;
		++fiftyMove;
		whiteTurn = !whiteTurn;
		if (p1->getType() == 'K') setKingPos(true, x2, y2);
		if (p1->getType() == 'k') setKingPos(false, x2, y2);
		reAttachAll();
		record.push_back(tempRecord);
		if (p2 or p3 or p1->getType() == 'P' or p1->getType() == 'p') {fiftyMove = 0;}
		return;
	} else {
		removePiece(x2, y2);
		placePiece(p1, x1, y1);
		if (p2) {
			placePiece(p2, x2, y2);
			reAttachAll();
			td->comeNotify(p2, p2->getColour());
			if (p2->getColour()) {
				removeFromVector(x2, y2, 3);
                                addToVector(p2, 1);
			} else {
                                removeFromVector(x2, y2, 4);
                                addToVector(p2, 2);
			}
			p2->setTakenOut(0);
		}
		if (p3) {
			placePiece(p3, x2, y1);
			reAttachAll();
			td->comeNotify(p3, p3->getColour());
                        if (p3->getColour()) {
                                removeFromVector(x2, y1, 3);
                                addToVector(p2, 1);
                        } else {
                                removeFromVector(x2, y1, 4);
                                addToVector(p2, 2);
                        }
			p3->setTakenOut(0);
		}
		reAttachAll();
		if (!safe) { throw "Invalid move, you are under check!";}
		if (safe) {throw "Invalid move, expose your king!";}
	}
	// consider castling and en passant here.
}

void Grid::undo() {
	if (totalMoveCount-1 < 0) return;
	string last = record.back();
    int x1 = last[0]-48;int y1 = last[1]-48;int x2 = last[2]-48;int y2 = last[3]-48;
	Piece *p1 = getCellAddress(x2,y2)->returnPiece();
	if (last.length() != 6) {removePiece(x2, y2);td->leaveNotify(x2, y2);placePiece(p1, x1, y1);td->comeNotify(p1, p1->getColour()); p1->subStep();}
	if (last.length() == 6) {remove(x2, y2); p1->subStep();}
	if (p1->getType() == 'K') setKingPos(true, x1, y1);
	if (p1->getType() == 'k') setKingPos(false, x1, y1);
	if ((p1->getType() == 'K' or p1->getType() == 'k') and (x1 - x2 == 2 or x2 - x1 == 2)) {
		if (x2 == 6) {
			Piece *rook = getCellAddress(5,y2)->returnPiece();
			removePiece(5,y2);
			td->leaveNotify(5, y2);
			placePiece(rook, 7, y2);
			td->comeNotify(rook, rook->getColour());
		} else if (x2 == 2) {
			Piece *rook = getCellAddress(3,y2)->returnPiece();
			removePiece(3,y2);
			td->leaveNotify(3, y2);
			placePiece(rook, 0, y2);
			td->comeNotify(rook, rook->getColour());
		}
	}
	if ((p1->getType() == 'P' or p1->getType() == 'p') and ( y1 - y2 == 2 or y2 - y1 == 2)) {
		p1->setForward(0);
	}	
	if (last.length() == 5 or (last.length() == 6 and last[4] != ' ')) { // something got eliminated
		if (whiteTurn) { // black moved before, white piece were taken out.
                        Piece *p2 = nullptr;
                        for (unsigned int i = 0; i < whiteGarbageCollector.size(); ++i) {
                                if (whiteGarbageCollector[i]->getTakenOut() == totalMoveCount-1) {
                                        p2 = whiteGarbageCollector[i]; whiteGarbageCollector.erase(whiteGarbageCollector.begin()+i); break;
                                }
                        }
			if (p2) {place(p2, p2->getX(), p2->getY());}
                } else {
                        Piece *p2 = nullptr;
                        for (unsigned int i = 0; i < blackGarbageCollector.size(); ++i) {
                                if (blackGarbageCollector[i]->getTakenOut()== totalMoveCount-1) {
                                        p2 = blackGarbageCollector[i]; blackGarbageCollector.erase(blackGarbageCollector.begin()+i); break;
                                }
                        }
			if (p2) {place(p2, p2->getX(), p2->getY());}
                }
	}
	if (last.length() == 6) {
		if (whiteTurn) {
			Piece *p3 = nullptr;
			for (unsigned int i = 0; i < blackGarbageCollector.size(); ++i) {
                                if (blackGarbageCollector[i]->getTakenOut()== totalMoveCount-1) {
                                        p3 = blackGarbageCollector[i]; blackGarbageCollector.erase(blackGarbageCollector.begin()+i); break;
                                }
                        }
                        if (p3) {place(p3, x1,y1);p3->subStep();}
		} else {
			Piece *p3 = nullptr;
                        for (unsigned int i = 0; i < whiteGarbageCollector.size(); ++i) {
                                if (whiteGarbageCollector[i]->getTakenOut() == totalMoveCount-1) {
                                        p3 = whiteGarbageCollector[i]; whiteGarbageCollector.erase(whiteGarbageCollector.begin()+i); break;
                                }
                        }
                        if (p3) {place(p3, x1, y1);p3->subStep();}
		}
	}
	whiteTurn = !whiteTurn;
	reAttachAll();
	record.pop_back();
	--totalMoveCount;
}

bool Grid::badMove(int x1, int y1, int x2 ,int y2) {
	try {
		move(x1, y1, x2, y2);
        	undo();
        	reAttachAll();
		return false;
	} catch (const char* msg) {
		return true;
	}
}

bool Grid::noLegalMoves(bool c) {
    if (c) {
		int size = whitePieces.size();
		for (int i = 0; i < size; ++i) {
			if (!whitePieces[i]->cantMove(this)) return false;
		}
		return true;
	} else {
		int size = blackPieces.size();
                for (int i = 0; i < size; ++i) {
                        if (!blackPieces[i]->cantMove(this))
                        {
                            return false;
                        }
                }
                return true;
	}
}

void Grid::gameover() {
	string newGame = "\nWant to start a new game?(y/n)";
	if (safeCheck(whiteTurn) and noLegalMoves(whiteTurn)) {whiteWins += 0.5; blackWins += 0.5; clean();running = false; fiftyMove = 0; throw ("Draw." + newGame);}
	if (whiteTurn) {
        if (!safeCheck(true) and noLegalMoves(true)) {++blackWins; running = false; fiftyMove = 0;clean(); throw ("Checkmate! Black player won." + newGame);}
	} else {
		if (!safeCheck(false) and noLegalMoves(false)) {++whiteWins;clean(); running = false; fiftyMove = 0; throw ("Checkmate! White player won" + newGame);}
	}
	if (fiftyMove >= 100) {whiteWins += 0.5; blackWins += 0.5;clean(); running = false; fiftyMove = 0; throw ("Draw because no capture or pawn move in past fifty plays." + newGame);}
}

int printhelp(Cell *c) {
	if (c->getOccupiedState() == 0) return 0;
	char temp = c->returnPiece()->getType();
	if (temp == 'K') return 6;
	if (temp == 'k') return -6;
	if (temp == 'Q') return 5;
	if (temp == 'q') return -5;
	if (temp == 'R') return 4;
        if (temp == 'r') return -4;
	if (temp == 'B') return 3;
        if (temp == 'b') return -3;
        if (temp == 'N') return 2;
        if (temp == 'n') return -2;
        if (temp == 'P') return 1;
        else return -1;
}

void Grid::prettyprint() {
	cout << "Occupied state\twhite attack range\tblack attack range" << endl;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			int temp = printhelp(getCellAddress(j,i));
			if (temp >= 0) cout << " " << printhelp(getCellAddress(j,i)) << " ";
			else cout << printhelp(getCellAddress(j,i)) << " ";
		}
		cout << "|";
		for (int j = 0; j < 8; ++j) {
			cout << getCellAddress(j,i)->whiteThreatenState() << " ";
		}
		cout << "|";
                for (int j = 0; j < 8; ++j) {
                        cout << getCellAddress(j,i)->blackThreatenState() << " ";
                }
		cout << endl;
	}
}
ostream &operator<<(ostream &out, const Grid &g) {
	out << *g.td;
	int wSize = g.whitePieces.size(); int bSize = g.blackPieces.size();
	int wbSize = g.whiteGarbageCollector.size(); int bbSize = g.blackGarbageCollector.size();
	out << "White Pieces on the board:";
	for (int i = 0; i < wSize; ++i) { out << " " << g.whitePieces[i]->getType();}
	out << "\nBlack Pieces on the board:";
	for (int i = 0; i < bSize; ++i) { out << " " << g.blackPieces[i]->getType();}
	out << "\nWhite Bin:";
        for (int i = 0; i < wbSize; ++i) { out << " " << g.whiteGarbageCollector[i]->getType();}
        out << "\nBlack Bin:";
        for (int i = 0; i < bbSize; ++i) { out << " " << g.blackGarbageCollector[i]->getType();}
	out << endl;
	/*int rSize = g.record.size();
	for (int i = 0; i < rSize; ++i) {
		out << g.record[i] << endl; 
	}*/
	return out;
}
