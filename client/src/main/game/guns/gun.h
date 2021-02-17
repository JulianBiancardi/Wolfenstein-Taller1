#ifndef GUN_H
#define GUN_H

#include <memory>
#include <unordered_map>

#include "../../../../../common/src/main/utils/base_map.h"
#include "../entities/drawable.h"
#include "../entities/identifiable_object.h"
#include "hit.h"

#define PIXEL 1

enum animation_state { stop, play };

class Gun : public Drawable {
 protected:
  double max_range;
  double min_range;
  animation_state animation = stop;
  Uint32 sprite_x = 0;

  virtual Hit shoot(
      Object& player, int& current_bullets, BaseMap& map,
      std::vector<std::weak_ptr<IdentifiableObject>>& players) = 0;
  std::shared_ptr<IdentifiableObject> trayectory(
      Ray& bullet, BaseMap& map,
      std::vector<std::weak_ptr<IdentifiableObject>>& players);

 public:
  explicit Gun(double min_range, double max_range);
  ~Gun();
  virtual Hit trigger(
      Object& player, int& current_bullets, BaseMap& map,
      std::vector<std::weak_ptr<IdentifiableObject>>& players) = 0;
  virtual void untrigger() = 0;
};

#endif
