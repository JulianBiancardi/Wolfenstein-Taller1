#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_OBJECT_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_OBJECT_H_

#include "../collisions/mask.h"

class Object {
 protected:
  Point center;
  Mask *mask;

 public:
  Object(Point center) : center(center) {}
  Mask *get_mask() { return mask; };
  Point get_position() { return center; };
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_OBJECT_H_
