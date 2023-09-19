#ifndef CAR_H
#define CAR_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Maze;

using namespace std;

class Car {
private:
  int x, y;
  bool direction; // if true its north/south ,if false its west/east
  Car *prev;

public:
  Car(int X, int Y, bool direction);
  int getY();
  int getX();
  bool getDirection();
  void setX(int x);
  void setY(int y);
  void setDirection(bool direction);
  unsigned long getKey() {
    unsigned long k = x * 100 + y * 10 + this->getDirection();
    return k;
  }
  bool goUp(Car &n, Maze &m);
  bool goDown(Car &n, Maze &m);
  bool goLeft(Car &n, Maze &m);
  bool goRight(Car &n, Maze &m);
  vector<Car *> expand(Maze &m);
  void setPrevious(Car *p) { prev = p; }
  Car *getPrevious() const { return prev; }
  bool operator==(const Car &o) const;
  int getDepth();
};

#endif // CAR_H