#ifndef CROSS_H
#define CROSS_H

#include "point_item.h"

class Cross : public PointItem {
 public:
  Cross(const Point& center, unsigned int id);
};

#endif
