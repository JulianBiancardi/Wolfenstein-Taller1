#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_OBJECT_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_OBJECT_H_

#include "../collisions/mask.h"

class Object {
 protected:
  Mask *mask;

 public:
  bool occupies(Point where);
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_OBJECTS_OBJECT_H_
