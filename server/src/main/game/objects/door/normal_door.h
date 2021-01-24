#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_DOOR_NORMAL_DOOR_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_DOOR_NORMAL_DOOR_H_

#include "door.h"

class NormalDoor : public Door {
 public:
  NormalDoor(const Point& center);
  void interact(Player& who, CollisionChecker& checker) override;
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_DOOR_NORMAL_DOOR_H_
