#ifndef GUN_H
#define GUN_H
#include <random>

#include "../../config_loader.h"
#include "../player.h"

class Shooter;
class Map;  // borrar

class Gun {
 protected:
  double max_range;
  double min_range;

 public:
  Gun(double min_range, double max_range);
  virtual int shoot(Player& player_shooting, int& current_bullets,
                    Map& map) = 0;
};
#endif
