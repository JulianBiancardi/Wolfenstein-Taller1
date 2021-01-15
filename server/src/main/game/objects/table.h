#ifndef TABLE_H
#define TABLE_H

#include "../../../../../common/src/main/collisions/box_mask.h"
#include "../../../../../common/src/main/object.h"

class Table : public Object {
 public:
  Table(double width, double length, Point center)
      : Object(center, 0,
               new BoxMask(width, length, this->position.get_ref_origin())) {}
};

#endif
