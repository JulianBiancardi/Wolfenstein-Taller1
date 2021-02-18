#ifndef MACHINE_GUN_H
#define MACHINE_GUN_H

#include <memory>
#include <random>
#include <vector>

#include "../../../../../common/src/main/utils/base_map.h"
#include "../entities/object.h"
#include "gun.h"
#include "hit.h"
#include "spray.h"

class MachineGun : public Gun {
 private:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution;
  Spray spray;
  double slope;
  double intercept;
  long last_shot_time;
  long last_burst_time;
  char bullet_count;

  double linear_func(double x);

  Hit shoot(Object& player, BaseMap& map,
            std::vector<std::weak_ptr<IdentifiableObject>>& players) override;

 public:
  MachineGun();
  ~MachineGun();

  /* Updates the gun appropriately and returns a Hit instance with
   * any relevant information.
   * Receives a player (or an object with his location), a bool indicating
   * whether the gun trigger is being pressed, a map valid for RayCasting and a
   * list of all the players.
   */
  Hit update(Object& player, bool trigger, BaseMap& map,
             std::vector<std::weak_ptr<IdentifiableObject>>& players);
};

#endif
