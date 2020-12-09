#ifndef BOX_MASK_H
#define BOX_MASK_H

#include "../../../../../common/src/main/utils/point.h"
#include "mask.h"

class Box_mask : public Mask {
 private:
  double width;
  double height;

 public:
  Box_mask(double width, double height, const Point &center)
      : width(width), height(height), Mask(center) {}

  virtual bool occupies(Point where);
};

#endif
