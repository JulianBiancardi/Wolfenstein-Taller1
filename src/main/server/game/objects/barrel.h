#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_BARREL_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_BARREL_H_

#include "../collisions/circle_mask.h"
#include "object.h"

class Barrel : public Object {
 public:
  Barrel(double radio, Point center)
      : Object(center) {
    mask = new Circle_mask(radio);
  }
  ~Barrel() {
    delete mask;
  }
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_BARREL_H_
