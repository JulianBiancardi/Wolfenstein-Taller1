#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_TABLE_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_TABLE_H_

#include "../collisions/box_mask.h"
#include "sprite.h"

class Table : public Sprite {
 public:
  Table(double width, double length, Point center) {
    mask = new Box_mask(width, length, center);
  }
  ~Table() { delete mask; }
};

#endif  // WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_TABLE_H_
