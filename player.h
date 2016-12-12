#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <vector>
#include "piece.h"
//#include "ai.h"

class Player {
	bool whitePlayer;
	std::vector<Piece *> myPieces;
	int pieceSize = 0;

	bool check;
	bool human;
	bool turn;
	int aiLevel; // equals 0 when human involves.
	//AI ai;
	int kCount=0;
public:
	Player(bool color, bool human, bool turn);
	~Player();

	bool getPlayer() const;
	bool checkState() const;
	bool checkMate();
	void attachPiece(Piece *p);
	void detachPiece(Piece *p);
	void changeTurn();
	void setAILevel(int i);
	int getKing() const;
	void addKing();	
	void removeKing();

	bool noLegalMoves();
	
};


#endif
