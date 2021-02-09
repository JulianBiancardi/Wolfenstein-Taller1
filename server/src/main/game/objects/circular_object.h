#ifndef CIRCULAR_OBJECT_H
#define CIRCULAR_OBJECT_H

#include "../collisions/circle_mask.h"
#include "object.h"

class CircularObject : public Object {
 public:
  CircularObject(double radius, const Point& center)
      : Object(center, 0,
               new CircleMask(radius, this->position.get_ref_origin())) {}
};

#endif
