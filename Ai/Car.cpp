#include "Car.h"
#include "Maze.h"
#include <iostream>

Car::Car(int X, int Y, bool direction) {
  x = X;
  y = Y;
  this->direction = direction;
  setPrevious(nullptr);
}

bool Car::goUp(Car &n, Maze &m) {
  if (getY() < HEIGHT - 1 && m.isFree(getX(), getY() + 1)) {
    n = *this;
    n.setY(n.getY() + 1);
    n.setPrevious(this);
    return true;
  } else if (getY() == HEIGHT - 1) {
    n = *this;
    m.remove(n);
    n.setX(-1);
    n.setY(-1);
    n.setPrevious(this);
    return true;
  }
  return false;
}

bool Car::goDown(Car &n, Maze &m) {
  if (getY() > 0 && m.isFree(getX(), getY() - 1)) {
    n = *this;
    n.setY(n.getY() - 1);
    n.setPrevious(this);
    return true;
  } else if (getY() == 0) {
    n = *this;
    m.remove(n);
    n.setX(-1);
    n.setY(-1);
    n.setPrevious(this);
    return true;
  }
  return false;
}
bool Car::goLeft(Car &n, Maze &m) {
  if (getX() > 0 && m.isFree(getX() - 1, getY())) {
    n = *this;
    n.setX(n.getX() - 1);
    n.setPrevious(this);
    return true;
  } else if (getX() == 0) {
    n = *this;
    m.remove(n);
    n.setX(-1);
    n.setY(-1);
    n.setPrevious(this);
    return true;
  }
  return false;
}
bool Car::goRight(Car &n, Maze &m) {
  if (getX() < WIDTH - 1 && m.isFree(getX() + 1, getY())) {
    n = *this;
    n.setX(n.getX() + 1);
    n.setPrevious(this);
    return true;
  } else if (getX() == WIDTH - 1) {
    n = *this;
    m.remove(n);
    n.setX(-1);
    n.setY(-1);
    n.setPrevious(this);
    return true;
  }
  return false;
}

vector<Car *> Car::expand(Maze &m) {
  bool dir = this->getDirection();
  vector<Car *> children;
  Car *child;
  if (dir == true) {
    child = new Car(*this);
    if (goUp(*child, m))
      children.push_back(child);
    else
      delete child;
    child = new Car(*this);
    if (goDown(*child, m))
      children.push_back(child);
    else
      delete child;
  }

  if (dir == false) {
    child = new Car(*this);
    if (goLeft(*child, m)) {
      children.push_back(child);
    } else
      delete child;
    child = new Car(*this);
    if (goRight(*child, m)) {
      children.push_back(child);
    } else
      delete child;
  }
  child = new Car(*this);
  return children;
}

void Car::setX(int X) { x = X; }

void Car::setY(int Y) { y = Y; }

int Car::getX() { return x; }

int Car::getY() { return y; }

bool Car::operator==(const Car &s) const { return (x == s.x && y == s.y); }

bool Car::getDirection() { return direction; }

int Car::getDepth() {
  int counter = 0;
  Car *c = this;
  while (c->prev != nullptr) {
    c = c->prev;
    counter++;
  }
  return counter;
}