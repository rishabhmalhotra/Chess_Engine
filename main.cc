#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unistd.h>
#include <fstream>
#include "grid.h"
#include "piece.h"
#include "cell.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "window.h"
#include "ai.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
//#include "level4.h"

using namespace std;

void defaultSetup(Grid &g) {
    for (int i = 0; i < 8; ++i) {
        Piece *wp = new Pawn('P');
        g.place(wp, i, 6);
        Piece *bp = new Pawn('p');
        g.place(bp, i, 1);
    }
    Piece *wk = new King('K');g.place(wk, 4, 7);
    Piece *wq = new Queen('Q');g.place(wq, 3, 7);
    Piece *wr1 = new Rook('R');g.place(wr1, 0, 7);
    Piece *wr2 = new Rook('R');g.place(wr2, 7, 7);
    Piece *wn1 = new Knight('N');g.place(wn1, 1, 7);
    Piece *wn2 = new Knight('N');g.place(wn2, 6, 7);
    Piece *wb1 = new Bishop('B');g.place(wb1, 2, 7);
    Piece *wb2 = new Bishop('B');g.place(wb2, 5, 7);
    Piece *bk = new King('k');g.place(bk, 4, 0);
    Piece *bq = new Queen('q');g.place(bq, 3, 0);
    Piece *br1 = new Rook('r');g.place(br1, 0, 0);
    Piece *br2 = new Rook('r');g.place(br2, 7, 0);
    Piece *bn1 = new Knight('n');g.place(bn1, 1, 0);
    Piece *bn2 = new Knight('n');g.place(bn2, 6, 0);
    Piece *bb1 = new Bishop('b');g.place(bb1, 2, 0);
    Piece *bb2 = new Bishop('b');g.place(bb2, 5, 0);
    g.setKingPos(true, 4, 7);
    g.setKingPos(false, 4, 0);
    g.reAttachAll();
}

bool validPlayer(string player) {
    if (player.length() == 5 and player == "human") {return true;}
    else if (player.length() == 9 and player.substr(0, 8) == "computer") {
        if (player[8] >= '1' and player[8] <= '4') {return true;}
    }
    return false;
}

bool validPos(string pos) {
    if (pos.length() == 2 and pos[0] >= 'a' and pos[0] <= 'h' and pos[1] >= '1' and pos[1] <= '8' ) return true;
    else return false;
}

bool validType(string s) {
    if (s.length() == 1 and (s[0]=='K' or s[0]=='k' or s[0]=='Q' or s[0]=='q' or 
                s[0]=='R' or s[0]=='r' or s[0]=='B' or s[0]=='b' or s[0]=='N' or s[0]=='n' or s[0]=='P' or s[0]=='p')) return true;
    else return false;
}

Piece *newPiece(char c, int &wkn, int &bkn) {
    if (c == 'K' or c == 'k') {
        if (c == 'K') ++wkn;
        if (c == 'k') ++bkn;
        return new King(c);
    }
    else if (c == 'Q' or c == 'q') return new Queen(c);
    else if (c == 'R' or c == 'r') return new Rook(c);
    else if (c == 'B' or c == 'b') return new Bishop(c);
    else if (c == 'N' or c == 'n') return new Knight(c);
    else if (c == 'P' or c == 'p') return new Pawn(c);
    return 0;
}

int main(int argc, char* argv[]) {
    ifstream file;
    vector<string> input;
    if (argc == 2) {
        string s;
        file.open(argv[1], ios::in);
        while (file >> s) {
            input.push_back(s);
            cout << s << endl;
        }
    }
    AI *ai1 = nullptr;
    AI *ai2 = nullptr;
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Grid g;
    bool whiteSetup = true;
    bool isWhiteAI = false;
    bool isBlackAI = false;
    int wkn = 0, bkn = 0;
    bool undoing = false;
    while (true) {
        while ( (isWhiteAI or isBlackAI) and g.getRunningState() and !undoing) {
	    if ((!isWhiteAI)&&(g.getTurn())) {
	     break;
	    }
            if (isWhiteAI && g.getTurn() && g.getRunningState()) {
                cout << "white ai is running\n";
		usleep(2000);
                ai1->makeMove();
                g.reAttachAll();
                cout << g;
                try {
                    g.gameover();
                    if ( !g.safeCheck(g.getTurn()) ) {
                        if (g.getTurn()) cout << "White king is in check." << endl;
                        else cout << "Black king is in check." << endl;
                    }
                    if ( !isBlackAI ) {break;}
                } catch (string& msg) {
                    cerr << msg << endl;
			cerr << "Keep going?(y/n)" << endl;
                    break;
                }
            }
	    if (isBlackAI && !g.getTurn() && g.getRunningState()) {
                cout << "black ai is running\n";
		usleep(2000);
                ai2->makeMove();
                g.reAttachAll();
                cout << g;
                try {
                    g.gameover();
                    if ( !g.safeCheck(g.getTurn()) ) {
                        if (g.getTurn()) cout << "White king is in check." << endl;
                        else cout << "Black king is in check." << endl;
                    }
                    if ( !isWhiteAI ) {break;}
                } catch (string& msg) {
                    cerr << msg << endl;
            		cerr << "Keep going?(y/n)" << endl;
	            break;
                }
            }
        }
        if (input.size() > 0) {cmd = input[0]; input.erase(input.begin());}
        else {cin >> cmd;}
        if (cmd == "analyze") {
            g.prettyprint();
        }
        else if (cmd == "new" or cmd == "y") {
            g.stopRunning();
	    g.clean();
            whiteSetup = true; isWhiteAI = false; isBlackAI = false;
            if (ai1) {delete ai1;}
	    if (ai2) {delete ai2;} // delete raises a seg fault.
            cout << "New game, please set players:\n";	
            string white, black;
            cin >> white >> black;
            while (!validPlayer(white) or !validPlayer(black)) {cerr << "Please enter valid player name."; cin >> white >> black;}
            if (white.length() == 9) {
                isWhiteAI = true;
                // init AI and set level
		if (white[8] == '1') {
                 ai1 = new Level1(&g, 1);
		} else if (white[8] == '2') {
		 ai1 = new Level2(&g, 1);
		} else if (white[8] == '3') {
		 ai1 = new Level3(&g, 1);
		}
	    }
            if (black.length() == 9) {
                isBlackAI = true;
                // init AI and set level as above
		if (black[8] == '1') {
			ai2 = new Level1(&g, 0);
		} else if (black[8] == '2') {
			ai2 = new Level2(&g, 0);
		} else if (black[8] == '3') {
  		ai2 = new Level3(&g, 0);
		}
            }
            cout << "White player is: " << white << ", black player is: " << black << endl;
        }
        else if (cmd == "quit" or cmd == "n"){
            if (ai1) delete ai1;
	    if (ai2) delete ai2;
		cout << "Final Score:\nWhite: " << g.getWins(1) << "\nBlack: " << g.getWins(0) << endl;
            break;
        }
        else if (cmd == "resign") {
            undoing = false;
	    whiteSetup = true; isWhiteAI = false; isBlackAI = false;
            whiteSetup = true;
            wkn = 0;
            bkn = 0;
            g.resign();
            g.stopRunning();
            cout << "Keep going?(y/n)";
        }
        else if (cmd == "undo") {
            if (!g.getRunningState()) { cerr << "The game is not running yet." << endl; }
            else {undoing = true; g.undo(); cout << g;}
        }
        else if (cmd == "move") {
	    undoing = false;
            string pos1, pos2;
            cin >> pos1 >> pos2;
            if (!g.getRunningState()) { cerr << "The game is not running yet." << endl; }
            else {
                while (!validPos(pos1) or !validPos(pos2)){ cin >> pos1 >> pos2; }
                int x1 = pos1[0] - 97, y1 = 56 - pos1[1], x2 = pos2[0] - 97, y2 = 56 - pos2[1];
                const Piece *temp = g.getCellAddress(x1, y1)->returnPiece();
                if (!temp) {cerr << "No piece on this cell." << endl;}
                else if (g.getTurn() != temp->getColour()) {cerr << "You can't move opponent's piece\n";}
                else {	
                    Piece *temp = g.getCellAddress(x1, y1)->returnPiece();
                    string newType = "";
                    if (temp) { if ((temp->getType() == 'P' and y2 == 0) or (temp->getType() == 'p' and y2 == 7)) cin >> newType;}
                    try {
                        g.move(x1, y1, x2, y2); 
                        cout << g;
                        if ((temp->getType() == 'P' and y2 == 0) or (temp->getType() == 'p' and y2 == 7)) {
                            while (!validType(newType) or newType[0]=='K' or newType[0]=='k' or 
                                    (90-newType[0])*(90-temp->getType() < 0)) { cin >> newType; }
                            temp->setTakenOut(g.moveCount()-1);
                            g.place(newPiece(newType[0], wkn, bkn), x2, y2);
                        }
                        g.reAttachAll();
                        if (validType(newType)) {g.updateRecord(newType); cout << g;}
                        if ( !g.safeCheck(g.getTurn()) ) {
                            if (g.getTurn()) cout << "White king is in check." << endl;
                            else cout << "Black king is in check." << endl;
                        
                        }
			try {g.gameover(); }
			catch (string& msg) { cerr << msg << endl; }
                    } catch (const char* msg) { cerr << msg << endl; }
                }
            }

        } else if (cmd == "setup") { // do we need a default setup
            wkn = 0; bkn = 0; whiteSetup = true;
            if (g.getRunningState()) cerr << "Not in setup mode." << endl;
            else {
                while (true) {
                    string setupCmd;
                    if (input.size() > 0) {setupCmd = input[0]; input.erase(input.begin());}
                    else {cin >> setupCmd;}
                    if (setupCmd == "=") {
                        string colour;
                        while (true) {
                            if (input.size() > 0) {colour = input[0]; input.erase(input.begin());}
                            else {cin >> colour;}
                            if (colour.compare("white") == 0) {
                                whiteSetup = true;
                                break;
                            } else if (colour.compare("black") == 0) {
                                whiteSetup = false;
                                break;
                            } else {
                                cerr << "Please enter a colour, either white or black." << endl;
                            }
                        }
                    } else if (setupCmd == "+") {
                        string type;
                        string pos;
                        if (input.size() > 1) {type = input[0]; input.erase(input.begin()); pos = input[0]; input.erase(input.begin());}
                        else {cin >> type >> pos;}
                        while (!validType(type) or !validPos(pos)) {cin >> type >> pos; } 
                        if ((type[0] <= 90 /*and whiteSetup*/) or (type[0] >= 97 /*and !whiteSetup*/)) {
                            Piece *p = newPiece(type[0], wkn, bkn);		
                            try {g.place(p, pos[0] - 97, 56 - pos[1]); cout << g;}
                            catch (const char* msg) { cerr << msg << endl; }
                        } else { cerr << "Not your turn to set up." << endl; }
                    } else if (setupCmd == "-") {
                        string pos;
                        if (input.size() > 0) {pos = input[0]; input.erase(input.begin());}
                        else {cin >> pos;}
                        while (!validPos(pos)) { cin >> pos; }
                        int x = pos[0] - 97, y = 56 - pos[1];
                        try {
                            Piece *temp = g.getCellAddress(x,y)->returnPiece();
                            if (!temp) cerr << "No piece on this cell." << endl;
                            else {
                                if (temp->getType() == 'K') --wkn;
                                if (temp->getType() == 'k') --bkn;
                                g.remove(x, y);
                                cout << g;
                            }
                        } catch (const char* msg) { cerr << msg << endl; }
                    } else if (setupCmd == "done") {
                        g.reAttachAll();
                        if (wkn == 1 and bkn == 1) {
                            if (g.safeCheck(1) and g.safeCheck(0)) { cerr << "End of setup mode." << endl; g.startRunning(); break;} 
                            else cerr << "Either or both kings are in check." << endl; 
                        } else { cerr << "The board should contains exactly one black king and one white king." << endl; }
                    } else if (setupCmd == "default") {
                        try {defaultSetup(g);}
                        catch (const char* msg) { cerr << msg << endl; }
                        cout << g;
                        g.startRunning();
                        break;
                    } else if (setupCmd == "analyze") {
                        g.prettyprint();
                    }
                }
            }
        }
    }
    if (argc == 2) {file.close();}
    return 0;
}

