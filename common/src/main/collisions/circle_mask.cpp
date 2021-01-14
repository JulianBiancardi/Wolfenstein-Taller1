#include "circle_mask.h"

Circle_mask::Circle_mask(double radio, const Point &center)
    : radio(radio), Mask(center) {}

bool Circle_mask::occupies(Point where) {
  return where.distance_from(center) < radio;
}

Circle_mask::~Circle_mask() {}