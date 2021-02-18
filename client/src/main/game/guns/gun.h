#ifndef GUN_H
#define GUN_H

#include <memory>
#include <unordered_map>

#include "../../../../../common/src/main/utils/base_map.h"
#include "../entities/drawable.h"
#include "../entities/identifiable_object.h"
#include "hit.h"

#define PIXEL 1

class Gun : public Drawable {
 protected:
  double max_range;
  double min_range;

  virtual Hit shoot(
      Object& player, BaseMap& map,
      std::vector<std::weak_ptr<IdentifiableObject>>& players) = 0;
  std::shared_ptr<IdentifiableObject> trayectory(
      Ray& bullet, BaseMap& map,
      std::vector<std::weak_ptr<IdentifiableObject>>& players);

 public:
  explicit Gun(double min_range, double max_range);
  ~Gun();

  /* Updates the gun appropriately and returns a Hit instance with
   * any relevant information.
   * Receives a player (or an object with his location),
   * his bullets, a bool indicating whether the gun trigger is being pressed, a
   * map valid for RayCasting and a list of all the players.
   */
  virtual Hit update(
      Object& player, bool trigger, BaseMap& map,
      std::vector<std::weak_ptr<IdentifiableObject>>& players) = 0;
};

#endif
