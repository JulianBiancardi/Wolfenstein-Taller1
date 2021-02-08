#ifndef BOX_MASK_H
#define BOX_MASK_H

#include "../../../../../common/src/main/utils/point.h"
#include "mask.h"

class BoxMask : public Mask {
 private:
  double width;
  double height;

 public:
  BoxMask(double width, double height, const Point& center)
      : width(width), height(height), Mask(center) {}

  bool occupies(const Point& where) const override;
};

#endif
