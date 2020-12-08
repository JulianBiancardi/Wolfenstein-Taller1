#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_MASK_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_MASK_H_

#include <cstddef>
#include "../../../utils/point.h"

class Circle_mask;

class Mask {
 public:
  virtual bool collides(size_t where_x,
                        size_t where_y,
                        Circle_mask &other,
                        Point other_position) = 0;
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_MASK_H_
