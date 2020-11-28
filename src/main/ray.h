#ifndef RAY_H
#define RAY_H

#include "point.h"

class Ray {
 private:
  Point origin;
  double angle;

 public:
  Ray(Point origin, double angle);
  ~Ray();
};

Ray::Ray(Point origin, double angle) : origin(origin), angle(angle) {}

Ray::~Ray() {}

#endif
