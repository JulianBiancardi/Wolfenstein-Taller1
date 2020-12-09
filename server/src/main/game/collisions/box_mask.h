#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_BOX_MASK_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_BOX_MASK_H_

#include "mask.h"

class Box_mask : public Mask {
 private:
  double width;
  double height;

 public:
  Box_mask(double width, double height, const Point &center)
      : width(width), height(height), Mask(center) {}

  virtual bool occupies(Point where);
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_BOX_MASK_H_
