#ifndef CHEST_H
#define CHEST_H

#include "point_item.h"

class Chest : public PointItem {
 public:
  Chest(const Point& center, unsigned int id);
};

#endif
