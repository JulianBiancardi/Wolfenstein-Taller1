#ifndef MASK_H
#define MASK_H

#include "../../../../../common/src/main/utils/point.h"

class Mask {
 protected:
  const Point& center;

 public:
  Mask(const Point& center) : center(center) {}
  virtual bool occupies(const Point& where) const = 0;
  const Point& get_center() { return center; }
  virtual ~Mask() {}
};

#endif
