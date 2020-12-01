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
  unsigned long term1 =
      ((long)(point1.x - point2.x)) * ((long)(point1.x - point2.x));
  unsigned long term2 =
      ((long)(point1.y - point2.y)) * ((long)(point1.y - point2.y));
  return sqrt(term1 + term2);
}