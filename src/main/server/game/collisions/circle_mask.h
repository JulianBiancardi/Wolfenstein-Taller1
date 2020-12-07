#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_

#include "box_mask.h"
#include "../../../point.h"
#include <cstddef>
#include <cmath>

class Map;

class Circle_mask {
 private:
  double radio;

 public:
  Circle_mask(double radio);
  ~Circle_mask() {};
  bool collides(size_t where_x, size_t where_y, Box_mask &other);
  bool collides(size_t where_x,
                size_t where_y,
                Circle_mask &other,
                Point other_position);
  bool collides_wall(size_t where_x,
                     size_t where_y,
                     Map &map,
                     double movement_angle);
  double get_radio() { return radio; };
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_
