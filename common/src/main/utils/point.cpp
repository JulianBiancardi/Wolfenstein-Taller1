#include "point.h"

#include <cmath>

#include "angle.h"

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point(const Point& other) : x(other.x), y(other.y) {}

Point& Point::operator=(const Point& other) {
  x = other.x;
  y = other.y;
  return *this;
}

Point::~Point() {}

bool Point::operator==(const Point& other) {
  return (this->x == other.x && this->y == other.y);
}

bool Point::operator!=(const Point& other) {
  return (this->x != other.x || this->y != other.y);
}

double Point::getX() const { return x; }

double Point::getY() const { return y; }

double Point::distance(const Point& point1, const Point& point2) {
  double term1 = (point1.x - point2.x) * (point1.x - point2.x);
  double term2 = (point1.y - point2.y) * (point1.y - point2.y);
  double norm = term1 + term2;
  return sqrt(norm);
}

double Point::distance_from(const Point& other) {
  return Point::distance(*this, other);
}

double Point::angle_to(const Point& other) {
  // Y grows going down
  return Angle::normalize(atan2(y - other.y, other.x - x));
}