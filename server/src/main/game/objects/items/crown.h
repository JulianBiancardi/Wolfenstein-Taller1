#ifndef CROWN_H
#define CROWN_H

#include "point_item.h"

class Crown : public PointItem {
 public:
  Crown(const Point& center, unsigned int id);
};

#endif
