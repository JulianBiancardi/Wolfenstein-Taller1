#ifndef CHAIN_CANNON_H
#define CHAIN_CANNON_H

#include <memory>
#include <random>
#include <vector>

#include "../../../../../common/src/main/utils/base_map.h"
#include "../entities/object.h"
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
            const std::vector<std::shared_ptr<Object>>& objects) override;

 public:
  ChainCannon();
  ~ChainCannon();

  Hit trigger(Object& player, int& current_bullets, BaseMap& map,
              const std::vector<std::shared_ptr<Object>>& objects) override;
  void untrigger() override;
};

#endif
