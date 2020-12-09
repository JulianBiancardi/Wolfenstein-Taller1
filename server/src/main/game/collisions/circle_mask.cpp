#include "circle_mask.h"

#include <cmath>

bool Circle_mask::occupies(Point where) {
  return where.distance_from(center) < radio;
}
