#ifndef TABLE_H
#define TABLE_H

#include "../collisions/box_mask.h"
#include "object.h"

class Table : public Object {
 public:
  Table(double width, double length, Point center)
      : Object(center, 0, new Box_mask(width, length, center)) {}
};

#endif
