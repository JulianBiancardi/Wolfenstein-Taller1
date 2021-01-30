#ifndef RECTANGULAR_OBJECT_H
#define RECTANGULAR_OBJECT_H

#include "../../../../../common/src/main/collisions/box_mask.h"
#include "../../../../../common/src/main/object.h"

class RectangularObject : public Object {
 public:
  RectangularObject(double width, double depth, Point center)
      : Object(center, 0,
               new BoxMask(width, depth, this->position.get_ref_origin())) {}
};

#endif
