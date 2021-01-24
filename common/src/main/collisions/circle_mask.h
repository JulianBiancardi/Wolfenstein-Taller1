#ifndef CIRCLE_MASK_H
#define CIRCLE_MASK_H

#include "mask.h"

class Map;

class CircleMask : public Mask {
 private:
  double radius;

 public:
  CircleMask(double radius, const Point& center);
  ~CircleMask();

  bool occupies(const Point& where) override;
  double get_radius() const;
};

#endif
