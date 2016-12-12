#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include <string>
#include "cell.h"
#include "display.h"
#include "piece.h"

class AI;

class Grid {
	std::vector<std::vector<Cell>> theGrid;  // The actual grid.
	float whiteWins, blackWins; // how many games white/black player won. 
	int wkx, wky, bkx, bky;
	int totalMoveCount = 1;
	bool running = false;

	TextDisplay *td; // The display.
	
	std::vector<Piece *> whitePieces;
	std::vector<Piece *> blackPieces;
	std::vector<Piece *> whiteGarbageCollector;
	std::vector<Piece *> blackGarbageCollector;

	bool whiteTurn = true;
	std::vector<std::string> record;
	int fiftyMove = 0;
public:
	Grid(); // initiate the game.
	~Grid(); // clean the grid. Calls when exits the program

	void updateRecord(std::string s);
	void clean();
	void startRunning();
	void stopRunning();

	void resign();
	int moveCount() const;
	bool getRunningState() const;
	bool getTurn() const;   
	float getWins(bool c) const;
	void setKingPos(bool c, int x, int y);
	//void setPlayers(std::string player1, std::string player2);
	Cell *getCellAddress(int x, int y);

	bool safeCheck(bool colour); //

	void addToVector(Piece *p, int which); // new

	void removeFromVector(int x, int y, int which); // new
	void reAttachAll();//new
	
	void removePiece(int x, int y); // removes piece at r, c.
	void placePiece(Piece *p, int x, int y); // places w/b players piece at x, y.

	void remove(int x, int y);
	void place(Piece *p, int x, int y);
	void move(int x1, int y1, int x2, int y2); // remove and place.	
	void undo();
	
	bool badMove(int x1, int y1, int x2, int y2);
	bool noLegalMoves(bool c);
	void gameover();
	void prettyprint();
	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
	friend class AI;
	friend class Level2;
	friend class Level3;
};

#endif
