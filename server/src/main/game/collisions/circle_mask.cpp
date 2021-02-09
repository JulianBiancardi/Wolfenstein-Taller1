#include "circle_mask.h"

CircleMask::CircleMask(double radius, const Point& center)
    : radius(radius), Mask(center) {}

bool CircleMask::occupies(const Point& where) const {
  return where.distance_from(center) <= radius;
}

double CircleMask::get_radius() const { return radius; };
