#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_DOOR_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_DOOR_H_

#include "../../../../../../common/src/main/object.h"
#include "../../player.h"
#include "../../collision_checker.h"

class Door : public Object {
 protected:
  Door(const Point& center);
  void change_state(CollisionChecker& checker);

 public:
  virtual void interact(Player& who, CollisionChecker& checker) = 0;
  bool is_open(); // Only used for testing
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_DOOR_H_
