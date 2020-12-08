#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_OBJECT_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_OBJECT_H_

#include "../collisions/mask.h"

class Sprite {
 protected:
  Point center;
  Mask *mask;

 public:
  Sprite(Point center) : center(center) {};
  bool occupies(Point where);
};

#endif  // WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_OBJECT_H_
