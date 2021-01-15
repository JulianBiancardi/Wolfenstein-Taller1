#ifndef BOX_MASK_H
#define BOX_MASK_H

#include "mask.h"

class BoxMask : public Mask {
 private:
  double width;
  double height;

 public:
  BoxMask(double width, double height, const Point& center)
      : width(width), height(height), Mask(center) {}

  bool occupies(Point& where) override;
};

#endif
