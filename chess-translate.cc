#include <iostream>
#include <string>
using namespace std;

// For translating chess input files that contain a board description to
// a format consisting of a sequence of setup mode commands.
// To use:
//   g++14 chess-translate.cc -o chess-translate
//   ./chess-translate < test-file-board-format.txt > test-file-setup-format.txt

int main() {
  cout << "setup\n";
  for(int row = 8; row >= 1; --row) {
    for(char col = 'a'; col <= 'h'; ++col) {
      char c;
      cin >> c;
      if (c != '_') {
        cout << "+ " << c << ' ' << col << row << '\n';
      }
    }
  }
  char move;
  if (cin >> move) {
    if (move == 'B' || move == 'b') cout << "= black\n";
    else if (move == 'W' || move == 'w') cout << "= white\n";
  }
  cout << "done" << endl;
}
