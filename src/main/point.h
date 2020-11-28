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

#endif
