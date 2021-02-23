#ifndef CIRCLE_MASK_H
#define CIRCLE_MASK_H

#include "../../../../../common/src/main/utils/point.h"
#include "mask.h"

class CircleMask : public Mask {
 private:
  double radius;

 public:
  CircleMask(double radius, const Point& center);

  /* Returns if the mask occupies the point sent or not */
  bool occupies(const Point& where) const override;

  /* Returns mask's radius */
  double get_radius() const;

  /* Returns a copy */
  Mask* get_copy(const Point& center) override;
};

#endif
