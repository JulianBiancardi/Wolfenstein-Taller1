#ifndef GUN_H
#define GUN_H

#include <random>
#include <vector>

#include "../../../../common/src/main/config_loader.h"
#include "../../../../common/src/main/object.h"
#include "../../../../common/src/main/utils/base_map.h"
#include "hit.h"

class Gun {
 protected:
  double max_range;
  double min_range;

 public:
  Gun(double min_range, double max_range);
  ~Gun();
  virtual Hit shoot(Object& player, int& current_bullets, BaseMap& map,
                    const std::vector<Object*>& objects) = 0;
};

#endif
