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
  void set_origin(double x, double y);
  double get_angle();
  void set_angle(double angle);
};

#endif
