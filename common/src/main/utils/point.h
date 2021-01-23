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

  bool operator==(const Point& other);
  bool operator!=(const Point& other);

  // Returns the X coordinate of the point.
  double getX() const;

  // Returns the Y coordinate of the point.
  double getY() const;

  // Calculates and returns the distance between two points.
  double static distance(const Point& point2, const Point& point1);

  // Calculates and returns the distance to another point.
  double distance_from(const Point& other) const;

  // Calculates and returns the angle between two points in the plane, using the
  // origin as the pivot.
  double angle_to(const Point& other);
};

#endif
