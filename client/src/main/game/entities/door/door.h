#ifndef BASE_DOOR_H
#define BASE_DOOR_H

#include "../drawable.h"
#include "door_state.h"

class Door : public Drawable {
 private:
  size_t x_pos;
  size_t y_pos;
  unsigned int resource_id;
  DoorState state;

 public:
  Door(size_t x, size_t y, unsigned int resource_id);
  ~Door();

  void open();
  void close();
  void update();

  virtual Image* get_image(ResourceManager& resource_manager) override;
  virtual SDL_Rect* get_slice(void* extra) override;
};

class pairHasher {
 public:
  std::size_t operator()(const std::pair<unsigned int, unsigned int>& k) {
    return (43 * k.first) % 1013 + (136 * k.second) % 1013;
  }
};

#endif
