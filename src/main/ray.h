#ifndef RAY_H
#define RAY_H

#include "point.h"

class Ray {
 private:
  Point origin;
  double angle;

 public:
  Ray(Point origin, double angle);
  Ray(int x, int y, double angle);
  ~Ray();

  Point get_origin();
  void set_origin(int x, int y);
  double get_angle();
  void set_angle(double angle);
};

#endif
