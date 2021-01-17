#ifndef GUN_H
#define GUN_H

#include <random>

#include "../../../../common/src/main/config_loader.h"
#include "../../../../common/src/main/object.h"
#include "../map.h"
#include "hit.h"

class Gun {
 protected:
  double max_range;
  double min_range;

 public:
  Gun(double min_range, double max_range);
  ~Gun();
  virtual Hit shoot(Object& player, int& current_bullets, Map& map) = 0;
};

#endif
