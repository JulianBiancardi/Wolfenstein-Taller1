#ifndef VERTICAL_DOOR_H
#define VERTICAL_DOOR_H

#include "base_door.h"

class VerticalDoor : public BaseDoor {
 private:
 public:
  VerticalDoor(size_t x, size_t y, unsigned int resource_id);
  ~VerticalDoor();

  bool update_collision(Collision& collision, double angle) override;

  virtual SDL_Rect* get_slice(void* extra) override;
};

#endif
