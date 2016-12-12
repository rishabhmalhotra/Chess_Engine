#include <iostream>
#include "display.h"
#include "piece.h"
#include <sstream>
using namespace std;

TextDisplay::TextDisplay() {
  int size = 60;
  xw = new Xwindow;
  //	xw->fillRectangle(0, 0, 800, 800, Xwindow::Black);

  for ( int i = 0; i < 8; ++i ) {
    vector<char> Row1;
    vector<char> Row2;
    vector<char> Row3;
    for ( int j = 0; j < 8; ++j ) {
      if ((i+j)%2 == 0) {
        Row1.push_back(' ');Row1.push_back(' ');Row1.push_back(' ');Row1.push_back(' ');
        Row2.push_back(' ');Row2.push_back(' ');Row2.push_back(' ');Row2.push_back(' ');
        Row3.push_back(' ');Row3.push_back(' ');Row3.push_back(' ');Row3.push_back(' ');
        xw->fillRectangle(j*size, i*size, size, size, Xwindow::Green);
      } else {
        Row1.push_back('*');Row1.push_back('*');Row1.push_back('*');Row1.push_back('*');
        Row2.push_back('*');Row2.push_back('*');Row2.push_back('*');Row2.push_back('*');
        Row3.push_back('*');Row3.push_back('*');Row3.push_back('*');Row3.push_back('*');
        xw->fillRectangle(j*size, i*size, size, size, Xwindow::Red);
      }       
    }
    theDisplay.push_back(Row1);
    theDisplay.push_back(Row2);
    theDisplay.push_back(Row3);

  }
  //draw axes
  for(int i = 0; i <= 7; i++)
  {
    std::string letter = "";
    char c = 65 + i;
    letter += c;
    xw->drawBigString(i*size+20, 525, letter, Xwindow::Blue);
    std::string number = "";
    c = 56-i;
    number += c;
    xw->drawBigString(505, i*size+40, number, Xwindow::Blue);
  }
}

void TextDisplay::clean() {
  int size = 60;
  for ( int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if ((i+j)%2 == 0) {theDisplay[i*3+1][j*4+1] = ' ';theDisplay[i*3+1][j*4+2] = ' ';xw->fillRectangle(j*size, i*size, size, size, Xwindow::Green);}
      else {theDisplay[i*3+1][j*4+1] = '*';theDisplay[i*3+1][j*4+2] = '*';xw->fillRectangle(j*size, i*size, size, size, Xwindow::Red);}
    }
  }
}

void TextDisplay::comeNotify(Piece *p, bool colour) {
  int size = 60;
  int x = p->getX();
  int y = p->getY();
  char type = p->getType();
  string piece = "";
  char c = p->getType();
  piece += c;
  if (type > 90) {
    theDisplay[3*y+1][4*x+1] = 'b';
    theDisplay[3*y+1][4*x+2] = type;
    xw->drawBigString(x*size+20, y*size+45, piece, Xwindow::Black);
  } else {
    theDisplay[3*y+1][4*x+1] = 'W';
    theDisplay[3*y+1][4*x+2] = type;
    xw->drawBigString(x*size+20, y*size+45, piece, Xwindow::White);
  }

}

void TextDisplay::leaveNotify(int x, int y) {
  int size = 60;
  if ((x+y)%2==0) {
    theDisplay[3*y+1][4*x+1] = ' ';
    theDisplay[3*y+1][4*x+2] = ' ';
    xw->fillRectangle(x*size, y*size, size, size, Xwindow::Green);
  }
  else {
    theDisplay[3*y+1][4*x+1] = '*';
    theDisplay[3*y+1][4*x+2] = '*';
    xw->fillRectangle(x*size, y*size, size, size, Xwindow::Red);
  }
}

TextDisplay::~TextDisplay() {delete xw;}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  out << "----------------------------------------" << endl;
  out << "------A---B---C---D---E---F---G---H-----" << endl;
  out << "----------------------------------------" << endl;
  for ( int i = 0; i < 24; ++i ) {
    if (i % 3 == 1) { out << '-' << 8- (i/3)<< "- ";}
    else { out << "--- ";}
    for ( int j = 0; j < 32; ++j ) {
      out << td.theDisplay[i][j];
    }
    if (i % 3 == 1) { out << " -" << 8- (i/3)<< '-';}
    else { out << " ---";}
    out <<  endl;
  }
  out << "----------------------------------------" << endl;
  out << "------A---B---C---D---E---F---G---H-----" << endl;
  out << "----------------------------------------" << endl;
  return out;
}
