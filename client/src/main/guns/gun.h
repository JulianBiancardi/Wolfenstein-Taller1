#ifndef GUN_H
#define GUN_H

#include <memory>
#include <random>
#include <vector>

#include "../../../../common/src/main/config_loader.h"
#include "../../../../common/src/main/utils/base_map.h"
#include "../object.h"
#include "hit.h"

class Gun {
 protected:
  double max_range;
  double min_range;
  virtual Hit shoot(Object& player, int& current_bullets, BaseMap& map,
                    const std::vector<std::shared_ptr<Object>>& objects) = 0;

 public:
  Gun(double min_range, double max_range);
  ~Gun();
  virtual Hit trigger(Object& player, int& current_bullets, BaseMap& map,
                      const std::vector<std::shared_ptr<Object>>& objects) = 0;
  virtual void untrigger() = 0;
};

#endif
