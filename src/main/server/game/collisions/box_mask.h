#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_BOX_MASK_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_BOX_MASK_H_

#include "mask.h"

class Box_mask : public Mask {
 private:
  double width;
  double height;

 public:
  Box_mask(double width, double height) : width(width), height(height) {}
  virtual bool collides(size_t where_x,
                        size_t where_y,
                        Circle_mask &other,
                        Point other_position);

};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_BOX_MASK_H_
