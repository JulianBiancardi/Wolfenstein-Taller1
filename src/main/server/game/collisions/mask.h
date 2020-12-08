#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_MASK_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_MASK_H_

#include <cstddef>
#include "../../../utils/point.h"

class Circle_mask;

class Mask {
 protected:
  Point center;

 public:
  Mask(Point center) : center(center) {}

  virtual bool occupies(Point where) = 0;
  void update_center(Point center) { this->center = center; }
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_MASK_H_
