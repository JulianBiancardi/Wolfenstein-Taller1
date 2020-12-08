#ifndef POINT_H
#define POINT_H

class Point {
 private:
  double x;
  double y;

 public:
  explicit Point(double x, double y);
  Point(const Point& other);
  Point& operator=(const Point& other);
  ~Point();

  double getX() const;
  double getY() const;
  double static distance(const Point& point2, const Point& point1);
};

#endif
