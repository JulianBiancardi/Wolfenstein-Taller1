#ifndef OBJECT_H
#define OBJECT_H

#include "collisions/mask.h"
#include "utils/ray.h"

class Object {
 protected:
  Ray position;
  Mask* mask;
  Object(Point position, double angle, Mask* mask);
  Object(Ray position, Mask* mask);

 public:
  ~Object();
  bool occupies(Point& where);
  Point get_position();
  double get_angle();
};

#endif
