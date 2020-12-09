#include "box_mask.h"
#include "circle_mask.h"
#include <cmath>

bool Box_mask::occupies(Point where) {
  double delta_x = abs(where.getX() - center.getX());
  double delta_y = abs(where.getY() - center.getY());

  return (delta_x < width / 2 && delta_y < height / 2);
}
