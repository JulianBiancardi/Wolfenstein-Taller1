#include "circle_mask.h"
#include <cmath>
#include "../../../map.h"

Circle_mask::Circle_mask(double radio) : radio(radio) {};

bool Circle_mask::collides(size_t where_x, size_t where_y, Box_mask &other) {
  return false;
}

bool Circle_mask::collides(size_t where_x,
                           size_t where_y,
                           Circle_mask &other,
                           Point other_position) {
  double distance = sqrt(pow(where_x - other_position.getX(), 2)
                             + pow(where_y - other_position.getY(), 2));
  return distance < (other.get_radio() + radio);
}

bool Circle_mask::collides_wall(size_t next_x,
                                size_t where_y,
                                Map &map,
                                double movement_angle) {
  double front_x = next_x + cos(movement_angle) * radio;
  double front_y = where_y + sin(movement_angle) * radio;

  if (map.is_wall(next_x, where_y) || map.is_wall(front_x, front_y))
    return true;

  return false;
}
