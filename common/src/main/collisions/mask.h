#ifndef MASK_H
#define MASK_H

#include "../utils/point.h"

class Mask {
 protected:
  const Point& center;

 public:
  Mask(const Point& center) : center(center) {}

  virtual bool occupies(const Point& where) = 0;
};

#endif
