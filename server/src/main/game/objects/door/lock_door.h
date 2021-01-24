#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_DOOR_LOCK_DOOR_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_DOOR_LOCK_DOOR_H_

#include "door.h"

class LockedDoor : public Door {
 private:
  bool locked;

 public:
  LockedDoor(const Point& center);
  void interact(Player& who, CollisionChecker& checker) override;
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_DOOR_LOCK_DOOR_H_
