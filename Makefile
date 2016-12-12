CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
XDISPLAY = -lX11
OBJECTS = main.o cell.o grid.o piece.o display.o king.o queen.o bishop.o knight.o rook.o pawn.o window.o ai.o level1.o level2.o level3.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${XDISPLAY}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
