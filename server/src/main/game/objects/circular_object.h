#ifndef CIRCULAR_OBJECT_H
#define CIRCULAR_OBJECT_H

#include "../../../../../common/src/main/collisions/circle_mask.h"
#include "../../../../../common/src/main/object.h"

class CircularObject : public Object {
 public:
  CircularObject(double radius, Point center)
      : Object(center, 0,
               new CircleMask(radius, this->position.get_ref_origin())) {}
};

#endif
