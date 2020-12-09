#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_MASK_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_MASK_H_

#include <cstddef>
#include "../../../utils/point.h"

class Circle_mask;

class Mask {
 protected:
  const Point &center;

 public:
  Mask(const Point &center) : center(center) {}

  virtual bool occupies(Point where) = 0;
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_MASK_H_
