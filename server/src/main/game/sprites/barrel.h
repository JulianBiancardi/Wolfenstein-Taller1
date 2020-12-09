#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_BARREL_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_BARREL_H_

#include "../collisions/circle_mask.h"
#include "sprite.h"

class Barrel : public Sprite {
 public:
  Barrel(double radio, Point center) { mask = new Circle_mask(radio, center); }
  ~Barrel() { delete mask; }
};

#endif  // WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_BARREL_H_
