#include <iostream>
#include "player.h"

Player::Player(bool color, bool human, bool turn):whitePlayer{color}, human{human}, turn{turn}, check{false} {}
Player::~Player(){}

bool Player::getPlayer() const { return human; }
bool Player::checkState() const { return check; }
bool Player::checkMate() { return false; }
void Player::attachPiece(Piece *p) { myPieces.push_back(p); ++pieceSize;}
void Player::detachPiece(Piece *p) {
	for ( int i = 0; i < pieceSize; ++i ) {
		if (myPieces[i]->getRow() == p->getRow() and myPieces[i]->getCol() == p->getCol()){
			--pieceSize;
			myPieces.erase(myPieces.begin() + i);
			break;
		} 
	}
}

void Player::setAILevel(int i) { aiLevel = i; }

int Player::getKing() const { return kCount; }
void Player::addKing() { ++kCount; }
void Player::removeKing() { --kCount; }

void Player::changeTurn() { turn = !turn; }

bool Player::noLegalMoves() { return false; } // modify later.
