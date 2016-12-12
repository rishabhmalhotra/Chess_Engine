#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"

class Piece;

class TextDisplay: public Observer {
	std::vector<std::vector<char>> theDisplay;
	Xwindow *xw;
public:
	TextDisplay();

	void clean();

	void comeNotify(Piece *p, bool colour);//override;
	
	void leaveNotify(int x, int y);

	~TextDisplay();

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
