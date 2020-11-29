#include "point.h"

#include <math.h>

Point::Point(int x, int y) : x(x), y(y) {}

Point::Point(const Point& other) : x(other.x), y(other.y) {}

Point& Point::operator=(const Point& other) {
  x = other.x;
  y = other.y;
  return *this;
}

Point::~Point() {}

int Point::getX() const { return x; }

int Point::getY() const { return y; }

double Point::distance(const Point& point1, const Point& point2) {
  int term1 = (point1.x - point2.x) * (point1.x - point2.x);
  int term2 = (point1.y - point2.y) * (point1.y - point2.y);
  return sqrt(term1 + term2);
}