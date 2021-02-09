#include "box_mask.h"

#include <cmath>

BoxMask::BoxMask(double width, double height, const Point& center)
    : width(width), height(height), Mask(center) {}

bool BoxMask::occupies(const Point& where) const {
  double delta_x = fabs(where.getX() - center.getX());
  double delta_y = fabs(where.getY() - center.getY());

  return (delta_x <= width / 2 && delta_y <= height / 2);
}
