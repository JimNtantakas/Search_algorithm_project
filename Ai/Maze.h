#ifndef MAZE_H
#define MAZE_H
#define WIDTH 8
#define HEIGHT 9
#include "Car.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Maze {
public:
  Maze();
  void setFree(int i, int j, int f);
  bool isFree(int x, int y);
  // void show();
  void add_car(Car &c);
  void remove(Car &c);

private:
  int free[WIDTH][HEIGHT];
};

#endif // MAZE_H
