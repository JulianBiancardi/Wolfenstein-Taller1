#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_BOX_MASK_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_BOX_MASK_H_

#include "../../../utils/point.h"

class Box_mask {
 private:
  Point &center;
  double width;
  double height;
};

#endif  // WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_BOX_MASK_H_
