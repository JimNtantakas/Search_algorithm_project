#include "Car.h"
#include "Maze.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

Car *BFS(Car *n, Maze *m, long long &examined, long long &mem) {
  queue<Car *> agenda;
  unordered_map<unsigned long, Car *> closed;
  m->setFree(n->getX(), n->getY(), 0);
  Car goal(-1, -1, n->getDirection());
  agenda.push(n);
  examined = 0;
  mem = 1;
  while (agenda.size() > 0) {
    if (agenda.size() + closed.size() > mem)
      mem = agenda.size() + closed.size();
    Car *n = agenda.front();
    agenda.pop();
    if (closed.count(n->getKey()) == 0) {
      examined++;
      if (*n == goal) {
        return n;
      }
      pair<unsigned long, Car *> k(n->getKey(), n);
      closed.insert(k);
      vector<Car *> children = n->expand(*m);
      for (unsigned int i = 0; i < children.size(); i++)
        if (closed.count(children[i]->getKey()) == 0) {
          agenda.push(children[i]);
        }
    }
  }
  m->setFree(n->getX(), n->getY(), 2);
  return nullptr;
}

int main() {
  long long mem, examined;
  Maze m;
  srand(time(NULL));
  vector<Car *> cars;
  int car_num, x, y;
  bool direction;
  Car *c;
  Car *array[car_num];
  int obstacles;

  cout << "Enter the number of Cars: ";
  cin >> car_num;
  for (int i = 0; i < car_num; i++) {
    cout << "Give the car's x , y and direction (1 for north/east, 0 for "
            "west/south)"
         << endl;
    cin >> x;
    cin >> y;
    cin >> direction;
    cars.push_back(new Car(x, y, direction));
    m.add_car(*cars[i]);
  }
  cout << "Enter the number of Obstacles: ";
  cin >> obstacles;
  for (int i = 0; i < obstacles; i++) {
    cout << "Give the obstacle's x and y" << endl;
    cin >> x;
    cin >> y;
    m.setFree(x, y, 1);
  }

  int out = 0; // how many cars are outside map
  while (out < car_num) {
    for (int count = 0; count < car_num; count++) {
      if (!m.isFree(cars[count]->getX(), cars[count]->getY())) {
        if (cars[count]->getDirection()) {
          if ((m.isFree(cars[count]->getX(), cars[count]->getY() - 1) ||
               m.isFree(cars[count]->getX(), cars[count]->getY() + 1)) != 0) {
            c = BFS(cars[count], &m, examined, mem);
            if (c != nullptr) {
              cout << "for the car number: " << count << " "
                   << "Depth: " << c->getDepth() << ", Mem: " << mem
                   << ", Examined: " << examined << endl;
              out++;
            } else
              cout << "for the car number: " << count << " Problem unsolvable"
                   << endl;
          }
        } else {
          if ((m.isFree(cars[count]->getX() - 1, cars[count]->getY()) ||
               m.isFree(cars[count]->getX() + 1, cars[count]->getY())) != 0) {
            c = BFS(cars[count], &m, examined, mem);
            if (c != nullptr) {
              cout << "for the car number: " << count << " "
                   << "Depth: " << c->getDepth() << ", Mem: " << mem
                   << ", Examined: " << examined << endl;
              out++;
            } else
              cout << "for the car number: " << count << " Problem unsolvable"
                   << endl;
          }
        }
      }
    }
  }
  return 0;
}
