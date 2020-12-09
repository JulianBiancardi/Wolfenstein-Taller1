#ifndef MASK_H
#define MASK_H

#include <cstddef>

#include "../../../../../common/src/main/utils/point.h"

class Circle_mask;

class Mask {
 protected:
  const Point &center;

 public:
  Mask(const Point &center) : center(center) {}

  virtual bool occupies(Point where) = 0;
};

#endif
