#include "box_mask.h"
#include "circle_mask.h"
#include <cmath>

bool Box_mask::collides(size_t where_x,
                        size_t where_y,
                        Circle_mask &other,
                        Point other_position) {
  double delta_x = abs(where_x - other_position.getX());
  double delta_y = abs(where_y - other_position.getY());

  if (delta_y < height / 2) {
    if (delta_x >= width / 2 + other.get_radio())
      return false;
    else
      return true;
  }

  if (delta_x < width / 2) {
    if (delta_y >= height / 2 + other.get_radio())
      return false;
    else
      return true;
  }

  double dx = delta_x - width / 2;
  double dy = delta_y - height / 2;

  return (sqrt(pow(dx, 2) + pow(dy, 2)) < other.get_radio());
}
