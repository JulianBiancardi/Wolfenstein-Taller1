#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_

#include "box_mask.h"
#include "../../../point.h"
#include <cstddef>
#include <cmath>

class Map;

class Circle_mask {
 private:
  Point &center;
  double radio;

 public:
  Circle_mask(Point &center, double radio);
  ~Circle_mask() {};
  bool collides(Box_mask other);
  bool collides(Circle_mask other);
  bool collides_wall(size_t next_x,
                     size_t next_y,
                     Map &map,
                     double movement_angle);
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_
