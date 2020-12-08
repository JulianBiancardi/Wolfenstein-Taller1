#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_TABLE_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_TABLE_H_

#include "../collisions/box_mask.h"
#include "object.h"

class Table : public Object {
 private:
  double width;
  double length;

 public:
  Table(double width, double length, Point center)
      : width(width), length(length), Object(center) {
    mask = new Box_mask(width, length);
  }
  ~Table() {
    delete mask;
  }
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_TABLE_H_
