#include "circle_mask.h"
#include "../../../map.h"

Circle_mask::Circle_mask(Point &center, double radio) : center(center),
                                                        radio(radio) {};

bool Circle_mask::collides(Box_mask other) {
  return false;
}

bool Circle_mask::collides(Circle_mask other) {
  return false;
}

bool Circle_mask::collides_wall(size_t next_x,
                                size_t next_y,
                                Map &map,
                                double movement_angle) {
  double front_x = next_x + cos(movement_angle) * radio;
  double front_y = next_y + sin(movement_angle) * radio;

  if (map.is_wall(next_x, next_y) || map.is_wall(front_x, front_y))
    return true;

  return false;
}
