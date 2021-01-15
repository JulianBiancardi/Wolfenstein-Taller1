#ifndef BARREL_H
#define BARREL_H

#include "../../../../../common/src/main/collisions/circle_mask.h"
#include "../../../../../common/src/main/object.h"

class Barrel : public Object {
 public:
  Barrel(double radio, Point& center)
      : Object(center, 0,
               new CircleMask(radio, this->position.get_ref_origin())) {}
};

#endif
