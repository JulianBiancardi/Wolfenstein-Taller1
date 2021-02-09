#ifndef CUP_H
#define CUP_H

#include "point_item.h"

class Cup : public PointItem {
 private:
  Cup(const Point& center, int id);

 public:
  explicit Cup(const Point& center);

  /* Returns a copy of the element */
  Item* copy() override;
};

#endif
