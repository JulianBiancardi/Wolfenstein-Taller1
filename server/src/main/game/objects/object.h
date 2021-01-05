#ifndef OBJECT_H
#define OBJECT_H

#include "../../../../../common/src/main/utils/ray.h"
#include "../collisions/mask.h"

class Object {
 protected:
  Ray position;
  Mask* mask;
  Object(Point position, double angle, Mask* mask);

 public:
  ~Object();
  bool occupies(Point where);
};

#endif
