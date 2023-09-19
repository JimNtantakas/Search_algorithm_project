#include "Maze.h"
// include "Car.h"
#include <iostream>
using namespace std;

Maze::Maze() {
  for (int i = 0; i < WIDTH; i++)
    for (int j = 0; j < HEIGHT; j++)
      free[i][j] = 0;
}

void Maze::setFree(int i, int j, int f) { free[i][j] = f; }

bool Maze::isFree(int x, int y) {
  if (free[x][y] == 0)
    return true;
  else
    return false;
}

/*void Maze::show(){
  for (int i=HEIGHT-1;i>=0;i--){
    for (int j=0;j<WIDTH;j++){
      cout<<free[j][i]<<" ";
    }
  cout<<endl;
  }
}*/

void Maze::add_car(Car &c) { free[c.getX()][c.getY()] = 2; }

void Maze::remove(Car &c) { free[c.getX()][c.getY()] = 0; }
