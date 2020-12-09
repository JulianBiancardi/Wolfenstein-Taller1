#include "circle_mask.h"
#include <cmath>
#include "../../../map.h"

bool Circle_mask::occupies(Point where) {
  return where.distance_from(center) < radio;
}
