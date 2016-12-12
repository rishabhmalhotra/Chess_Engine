# Chess_Engine
Artificially intelligent chess engine with graphics built from ground up without using any existing databases/libraries(like Stockfish)

Chess: Final Design Document
Team:
Dhron Joshi(d8joshi), Haowei Guo(h48guo), and Rishabh Malhotra(r22malho) July 26, 2016



Image retrieved from
http://unconfirmedbreakingnews.com/wp-content/uploads/2014/09/chessboard1.jpg

Our project differed from our design because we needed to accommodate for the AI class and its subclasses to access information from our Cell, Piece, and Grid classes. Each level of the AI acts differently and needs to gain certain information from the board to perform those actions. The AI class wasn’t included in our initial UML because the core game needed to be completed first in order for us to begin thinking about implementing the AI class and its subclasses. Since we needed to accommodate for the AI class, we needed our Grid, Piece, and Cell classes to have additional methods to provide information to the AI.

Implementation Methods & Use of Design Patterns
• Observer Design Pattern
– The chess game functionality was entirely done by using the observer design pat- tern. This is because we felt the majority of the chess game is updating the board based on certain events, and we could encompass player movement, text and graphics display, and updating cells all in one design pattern. We decided that there was no need to include any other design patterns besides the observer. Part of designing and implementing good software is knowing what types of design practices best fit the goal you are trying to achieve; we believe only the observer design pattern was needed to accomplish our goal.
• Player Movement and Legal Piece Movement
– The player movement is implemented by having each subclass of the Piece class to contain a vector of it’s legal moves. When a piece moves, there is a loop that checks all legal moves of the piece and attaches it to it’s vector of legal moves. Then when a move command is issued, we check whether that position exists within our vector, and if it does, we move the piece. Each legal move for each piece is determined by the freedom of the cell on the board, and the unique movibility of each piece.
• Drawing and Updating Display
– The text display belongs to the TextDisplay class. The character components of the text display are stored in char vectors and are initialized in a standard chess board format within our TextDisplay constructor. The display is updated through our comeNotify(), (line 58, display.cc) and leaveNotify(), (line 88, display.cc) functions which alert the display to update whenever a piece is moved to a different coordinate on the board. We also overloaded the bitshift operator << to output our TextDisplay in our main function as we needed.
As the text display runs, we also implemented the X11/XWindow library to create a graphical window that represents the pieces on the board.
2
 – A graphical view of our board using X11.
– Two loops are used to draw the axes and are drawn during the creation of the win- dow. The green and red squares are also drawn upon creation. The pieces are con- tinuously redrawn as they move around the board upon the calls of comeNotify() and leaveNotify() as discussed above.
• Pawn Promotion
– This was accomplished by having an if statement check whether the pawn of the opposite colour reached the opposite side of the board. If the player is a human, we give the option to choose what piece you want the pawn to be; if the player is an AI, it chooses the queen by default. When the piece transforms, we remove the current piece and create a new piece from the subclass of the desired type, and so it possesses the correct properties of that piece.
• En Passant
– We have a condition that checks for the availability of the en passant move, and requires that the attacking pawn was moved into the position before the attack one move earlier. If these conditions are met, the en passant move is added to the legal moves of the pawn that wishes to attack, and then it may move in the position the pass the opponent pawn. Once that pawn moves, the en passant move is completed and the opponent pawn is removed from the board.
3
• Castling
We check whether the king and the rooks have been moved before using our stepCount() method and that they’re in their original position. If they haven’t been moved and are in their initial position, and there are no pieces between the king and the rook; if all these conditions are met, we attach the coordinate for castling in our legalMoves vector for our king, and then the king is able to castle. After the king has moved, we also move the rook to its corresponding place on the grid.
• AI Superclass
– The AI is the superclass that controls all the computer played levels. It has
Level1, Level2 and Level3.
– The AI specifies protected fields like objects of the Grid class, the colour that the AI is playing as and a vector of all the pieces that the AI has on the board at any given state of the game.
– Also,theAIsuperclassspecifiesimportantmethodslikethepurevirtualmakeMove() function, a function that generates a random number in a given range and another function that gets a random valid piece and supplies it to the AI to consider for movement.
• Level1 AI
– The level1 is a subclass of the AI superclass. It is the level where, the computer just makes legal random moves and doesnt exactly analyze whether it is making an intelligent move or not.
– The Level1 class has makeMove() method that generates a vector of vectors which it then passes to the generateMove(<vector <vector> >) function and then the generateMove() function generates a move.
– If this generated move is legal (valid; obeying the rules of the game), then the popCell() method of Level1 pops the small vector (one of the vectors inside the bigger vector) corresponding to this move from big vector.
• Level2 AI & Level3 AI
– These levels are also subclasses of the AI superclass. Level2 is the level where, the computer tries to capture the opponent pieces and prefers capturing moves over just legal random moves like in Level1 so that it is a bit higher in difficulty.
– Level3 is the level, where the difficulty actually rises because the AI in level3 doesnt just prefer capturing, rather, it plays defensively and aggressively. So, if a black bishop is diagonally opposite to a white pawn, instead of just moving forward to be in a safe zone, the site pawn would actually capture the black bishop (its predator).
4
– Also, Level3 has foresight, which means that it analyzes 2 moves at any given time; the move at hand and the prospective opponent move after the present move has been made. So, for this it uses various important methods of the Grid and the Piece classes like attackRange() or legalMoves() for a Piece and the reAttach() method of the Grid which makes itself useful in the case that an opponents pawn makes it to the end of the board and is replaced by another piece (Piece).
– For this, these classes use the methods randomMove() which generates random legal moves (to be used in the scenarios where the computer doesnt have anything to capture from the opponent or is not in any kind of danger in the present sce- nario) and makeMove() which does all the work of analyzing and seeing whether it can find anything worth capturing or defending or else it just calls randomMove().
3 Accommodation of Change
We had a very easy time adding in new methods and functions without changing any of our old implementations, and this allowed for us easily expanding and making methods to accommodate our AI classes.
Our Cell, Piece, Grid, and Display classes all have high cohesion as all of the functions implemented within the respective classes only perform actions pertaining to that class and provide a general interface to accessing information about that class; which is why we were able to give the AI classes the information that it needed to be implemented properly.
For example, when we wanted to implement an undo function so we can revert the state of the board, we already had a stack of moves in our grid class because the grid needs to keep track of the moves completed to maintain it’s state. The only changes we had to make was to pop the move off the record vector and update the grid accordingly.
We have also minimized coupling by using proper design styles such as encapsulation, we’ve minimized the number of friend classes to classes that absolutely require the members of a specific class. This also contributes to our accomodation of change because each individual class works entirely whenever we add or take away features from our program.
4 Answers to Provided Questions
Question: What lessons did this project teach you about developing software in teams? If
you worked alone, what lessons did you learn about writing large programs?
We definitely learned the importance of effectively communicating your work to others. We often found ourselves asking what eachother’s code did, and we found that if we could explain it effectively, it aided us in our debugging process. We learned about leaving com- ments in our implementations so others can follow and understand that we implemented; this improves readability and understanding for every member of our group.
We also learned how to consistently use version control (we used git.uwaterloo.ca) and maintained a document that acted as our TO-DO list, and so even if we worked at different
5
times, we would continuously update the repository to keep track of what we needed to accomplish.
We also learned about the importance of planning when working on a large project like this, and allocating our time and resources effectively so we don’t waste any time during the programming phase. We made quite a few changes to our UML document by the end of the project compared to the initial document.
In conclusion: collaboration, communication, planning, and time management are nec- essary skills when taking on a large software project such as this and we learned a lot about each of these aspects during the planning and development phase.
Question: What would you have done differently if you had the chance to start over?
We definitely would have planned out the UML document better to account for the AI class. If we had done that in the beginning, the AI development would have been completed much quicker than we had planned.
We would also look into smarter ways (more efficient ways) to implement each level of the AI. In our implementation, we have to analyze every situation and every piece on the board to make a proper decision on what to move; this becomes very taxing and inefficient: we would do some more research into the logic behind Chess AI before actually trying to implement something more sophisticated. Perhaps we would actually implement a chess engine to make sophisticated decisions for us such as Stockfish which we found on a Google search.
Also we would look into better graphics libraries or game development libraries that allow us to have more colours and have options for loading images and displaying them to the screen. We felt that X11/XWindow was very limited in terms of colours and not having any functionality to import images and to display/draw them onto the screen.
5 Answers to Due Date 1 Questions & Differences
Question: Chess programs usually come with a book of standard opening move sequences, which list accepted opening moves and responses to opponents’ moves, for the first dozen or so moves of the game. Although you are not required to support this, discuss how you would implement a book of standard openings if required.
This could be implemented using a map where instead of keys, we have an opponent’s move, and for values, we have our response; and feed those values into our interpreter. Since the opening moves are standardized, we only have to check a finite number of possible outcomes and do the appropriate response move.
After doing this project, we decided to consider having a vector of standard moves which we can randomly choose a move. The opponent would then read the latest move, and have a map where they move would match which a key, and the opponent would move with that corresponding key’s value.
Question: How would you implement a feature that would allow a player to undo his/her last move? What about an unlimited number of undos?
Use a Stack data structure to keep track of the coordinates that a piece moves to. Every 6
time a piece is moved, it’s movement is pushed onto the stack, and every time a player wants to undo, the movement is popped off the stack and the piece moves to its previous position. This would allow for unlimited player undoes. If we were to implement a single undo feature, we could only keep track of the previous move and revert the piece to that location only.
We actually implemented this using this exact logic so no changes were needed to the answer above.
Question: Variations on chess abound. For example, four-handed chess is a variant that is played by four players (search for it!). Outline the changes that would be necessary to make your program into a four-handed chess game.
We would first have to design a way to accommodate two more different colours to represent the four other players and make a sequence to cycle through all the four players’ turns. The rules for four player chess are the same as regular chess so there is no need to alter any of the checks or functionality that we already have.
We don’t have any changes to this response because we found that this question is essentially the same as implementing two chess games within the same chess game and just requires to cycle through the other players. The same classes that we have would work for a four player chess game.
6 Conclusion
In conclusion, we’ve learned a lot of software engineering and object-oriented techniques and practices over the term and had the opportunity to apply these skills while making a chess game. We’ve learned a lot in regards to working in a team setting and managing a large (in the context of this class) software project from start to finish. We’ve also done our best implement these software engineering technquies to accommodate for new changes and to make our program scalable if need be.
7
