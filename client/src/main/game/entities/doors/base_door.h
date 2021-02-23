#ifndef BASE_DOOR_H
#define BASE_DOOR_H

#include "../../../../../common/src/main/utils/point.h"
#include "../../rendering/collision.h"
#include "../drawable.h"
#include "door_state.h"

class BaseDoor : public Drawable {
 protected:
  size_t x_pos;
  size_t y_pos;
  unsigned int resource_id;
  DoorState state;

 public:
  BaseDoor(size_t x, size_t y, unsigned int resource_id);
  ~BaseDoor();

  void open();
  void close();
  void update();

  /* Receives a collision and updates it accordingly to the door and angle.
   * Returns true if the door is hit, false otherwise.
   */
  virtual bool update_collision(Collision& collision, double angle) = 0;
  bool requires_key();

  virtual Image* get_image(ResourceManager& resource_manager) override;
};

class PairHasher {
 private:
 public:
  size_t operator()(const std::pair<unsigned int, unsigned int>& key) const {
    return (43 * key.first) % 1013 + (136 * key.second) % 1013;
  }
};

#endif
