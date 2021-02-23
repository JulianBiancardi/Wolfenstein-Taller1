#ifndef KNIFE_H
#define KNIFE_H

#include <memory>
#include <random>
#include <vector>

#include "../../../../../common/src/main/utils/base_map.h"
#include "../entities/identifiable_object.h"
#include "gun.h"
#include "hit.h"

class Knife : public Gun {
 private:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution;
  Hit shoot(Object& player, BaseMap& map,
            std::vector<std::weak_ptr<IdentifiableObject>>& players) override;
  bool shot;

 public:
  explicit Knife(unsigned int resource_id);

  /* Updates the gun appropriately and returns a Hit instance with
   * any relevant information.
   * Receives a player (or an object with his location), a bool indicating
   * whether the gun trigger is being pressed, a map valid for RayCasting and a
   * list of all the players.
   */
  Hit update(Object& player, bool trigger, BaseMap& map,
             std::vector<std::weak_ptr<IdentifiableObject>>& players) override;

  SDL_Rect* get_slice(void* extra) override;
};

#endif
