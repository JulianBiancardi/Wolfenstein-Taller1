#ifndef CIRCLE_MASK_H
#define CIRCLE_MASK_H

#include "../utils/point.h"
#include "mask.h"

class CircleMask : public Mask {
 private:
  double radius;

 public:
  CircleMask(double radius, const Point& center);
  ~CircleMask();

  bool occupies(const Point& where) const override;
  double get_radius() const;
};

#endif
