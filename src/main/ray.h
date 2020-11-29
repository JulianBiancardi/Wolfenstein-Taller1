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
  double get_angle();
};

#endif
