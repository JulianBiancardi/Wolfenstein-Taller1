#ifndef PASSAGE_H
#define PASSAGE_H

#include "base_door.h"

class Passage : public BaseDoor {
 private:
  /* data */
 public:
  Passage(size_t x, size_t y, unsigned int resource_id);
  ~Passage();

  bool update_collision(Collision& collision, double angle) override;

  SDL_Rect* get_slice(void* extra) override;
};

#endif
