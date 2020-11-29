#ifndef POINT_H
#define POINT_H

class Point {
 private:
  int x;
  int y;

 public:
  explicit Point(int x, int y);
  Point(const Point& other);
  Point& operator=(const Point& other);
  ~Point();

  int getX() const;
  int getY() const;
  double static distance(const Point& point2, const Point& point1);
};

#endif
