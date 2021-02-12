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
  bool triggered;
  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            std::vector<std::weak_ptr<IdentifiableObject>>& players) override;

 public:
  Knife();

  Hit trigger(Object& player, int& current_bullets, BaseMap& map,
              std::vector<std::weak_ptr<IdentifiableObject>>& players) override;
  void untrigger() override;
};

#endif
