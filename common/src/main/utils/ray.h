#ifndef RAY_H
#define RAY_H

#include "angle.h"
#include "point.h"

class Ray {
 private:
  Point origin;
  Angle angle;

 public:
  Ray(Point origin, double angle);
  Ray(double x, double y, double angle);
  ~Ray();

  Point get_origin();
  const Point &get_ref_origin();
  double get_angle();
};

#endif
