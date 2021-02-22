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

  virtual bool update_collision(Collision& collision, double angle) = 0;

  virtual Image* get_image(ResourceManager& resource_manager) override;
  virtual SDL_Rect* get_slice(void* extra) override;
};

/*
struct CoordsKey {
  unsigned int x;
  unsigned int y;

  bool operator==(const CoordsKey& other) const {
    return (x == other.x && y == other.y);
  }
}; */

/*
namespace std {

template <>
struct hash<CoordsKey> {
  std::size_t operator()(const CoordsKey& k) const {
    size_t hash = (43 * k.x) % 1013 + (136 * k.y) % 1013;
    return hash;
  }
};

}  // namespace std
*/

class PairHasher {
 private:
 public:
  size_t operator()(const std::pair<unsigned int, unsigned int>& key) const {
    return (43 * key.first) % 1013 + (136 * key.second) % 1013;
  }
};

#endif
