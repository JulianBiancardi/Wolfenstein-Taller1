#include "point.h"

#include <cmath>
#include <iostream>  // TODO Delete

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
  unsigned long long term1 = ((long long)point1.x - (long long)point2.x) *
                             ((long long)point1.x - (long long)point2.x);
  unsigned long long term2 =
      ((long long)(point1.y - point2.y)) * ((long long)(point1.y - point2.y));
  unsigned long long norm = term1 + term2;
  return sqrt(norm);
}