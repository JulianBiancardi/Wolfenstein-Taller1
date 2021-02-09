#ifndef CROSS_H
#define CROSS_H

#include "point_item.h"

class Cross : public PointItem {
 private:
  Cross(const Point& center, int id);

 public:
  explicit Cross(const Point& center);

  /* Returns a copy of the element */
  Item* copy() override;
};

#endif
