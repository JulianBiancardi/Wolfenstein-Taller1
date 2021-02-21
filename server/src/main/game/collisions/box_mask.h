#ifndef BOX_MASK_H
#define BOX_MASK_H

#include "../../../../../common/src/main/utils/point.h"
#include "mask.h"

class BoxMask : public Mask {
 private:
  double width;
  double height;

 public:
  BoxMask(double width, double height, const Point& center);

  /* Returns if the mask occupies the point sent or not */
  bool occupies(const Point& where) const override;

  /* Returns a copy */
  Mask* get_copy(const Point& center) override;
};

#endif
