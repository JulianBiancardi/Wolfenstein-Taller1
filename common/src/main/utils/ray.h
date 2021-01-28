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

  Point get_origin() const;
  const Point &get_ref_origin() const;
  double get_angle() const;
};

#endif
