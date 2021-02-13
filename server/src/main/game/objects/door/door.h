#ifndef DOOR_H
#define DOOR_H

#include "../../collisions/collision_checker.h"
#include "../player.h"
#include "../object.h"

class Door : public Object, public Identifiable {
 protected:
  Door(const Point& center, unsigned int id);
  void change_state(CollisionChecker& checker);

 public:
  /* Returns if the door state changed */
  virtual bool interact(Player& who, CollisionChecker& checker) = 0;

  /* Returns if the door is open or not */
  bool is_open() const;

  /* Closes the door */
  void close(CollisionChecker& checker);
};

#endif
