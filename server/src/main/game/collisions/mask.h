#ifndef MASK_H
#define MASK_H

#include "../../../../../common/src/main/utils/point.h"

class Mask {
 protected:
  const Point& center;

 public:
  Mask(const Point& center) : center(center) {}
  virtual ~Mask() {}

  /* Returns if the mask occupies the point sent or not */
  virtual bool occupies(const Point& where) const = 0;

  /* Returns mask's center */
  const Point& get_center() { return center; }

  /* Returns a copy */
  virtual Mask* get_copy(const Point& center) = 0;
};

#endif
