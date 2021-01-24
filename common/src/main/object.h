#ifndef OBJECT_H
#define OBJECT_H

#include "collisions/mask.h"
#include "identifiable.h"
#include "utils/ray.h"

class Object : public Identifiable {
 protected:
  Ray position;
  Mask* mask;
  Object(Point position, double angle, Mask* mask);
  Object(Point position, double angle, Mask* mask, int id);
  Object(Ray position, Mask* mask, int id);
  Object(Ray position, Mask* mask);

 public:
  virtual ~Object();
  bool occupies(const Point& where);
  Point get_position();
  double get_angle();
};

#endif
