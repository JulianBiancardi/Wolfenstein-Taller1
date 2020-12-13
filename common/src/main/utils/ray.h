#ifndef RAY_H
#define RAY_H

#include "point.h"

class Ray {
 private:
  Point origin;
  double angle;

 public:
  Ray(Point origin, double angle);
  Ray(double x, double y, double angle);
  ~Ray();

  Point get_origin();
  void set_origin(const Point &origin);
  const Point &get_ref_origin();
  double get_angle();
};

#endif
