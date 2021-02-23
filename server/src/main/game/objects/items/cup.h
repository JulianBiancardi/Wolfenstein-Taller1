#ifndef CUP_H
#define CUP_H

#include "point_item.h"

class Cup : public PointItem {
 public:
  Cup(const Point& center, unsigned int id);
};

#endif
