#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_DOOR_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_DOOR_H_

#include "../../../../../../common/src/main/object.h"
#include "../../player.h"
#include "../../collision_checker.h"

class Door : public Object {
 protected:
  explicit Door(const Point& center);
  void change_state(CollisionChecker& checker);

 public:
  /* Returns if the door state changed */
  virtual bool interact(Player& who, CollisionChecker& checker) = 0;

  /* Returns if the door is open or not */
  bool is_open() const;

  /* Closes the door */
  void close(CollisionChecker& checker);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_OBJECTS_ITEMS_DOOR_H_
