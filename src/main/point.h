#ifndef POINT_H
#define POINT_H

class Point {
 private:
  int x;
  int y;

 public:
  explicit Point(int x, int y);
  ~Point();

  int getX();
  int getY();
};

Point::Point(int x, int y) : x(x), y(y) {}

Point::~Point() {}

int Point::getX() { return x; }

int Point::getY() { return y; }

#endif
