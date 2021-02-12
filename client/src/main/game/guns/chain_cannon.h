#ifndef CHAIN_CANNON_H
#define CHAIN_CANNON_H

#include <memory>
#include <random>
#include <unordered_map>

#include "../../../../../common/src/main/utils/base_map.h"
#include "../entities/identifiable_object.h"
#include "gun.h"
#include "hit.h"
#include "spray.h"

class ChainCannon : public Gun {
 private:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution;
  Spray spray;
  double slope;
  double intercept;
  long last_shot_time;
  bool triggered;

  double linear_func(double x);

  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            std::vector<std::weak_ptr<IdentifiableObject>>& players) override;

 public:
  ChainCannon();
  ~ChainCannon();

  Hit trigger(Object& player, int& current_bullets, BaseMap& map,
              std::vector<std::weak_ptr<IdentifiableObject>>& players) override;
  void untrigger() override;
};

#endif
