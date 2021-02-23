#ifndef HORIZONTAL_DOOR_H
#define HORIZONTAL_DOOR_H

#include "base_door.h"

class HorizontalDoor : public BaseDoor {
 private:
 public:
  HorizontalDoor(size_t x, size_t y, unsigned int resource_id);
  ~HorizontalDoor();

  bool update_collision(Collision& collision, double angle) override;

  virtual SDL_Rect* get_slice(void* extra) override;
};

#endif
