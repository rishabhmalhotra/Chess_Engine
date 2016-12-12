#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Piece;

class Observer {
 public:
  virtual void comeNotify(Piece *p, bool colour) = 0;
  virtual void leaveNotify(int x, int y) = 0;
  virtual ~Observer() = default;
};
#endif
