#ifndef WOLFENSTEIN_TALLER1_GUN_H
#define WOLFENSTEIN_TALLER1_GUN_H
#include <random>

#include "../../config_loader.h"
#include "../player.h"

class Shooter;
class Map; //borrar

class Gun {
 public:
  Gun();
  virtual int shoot(Shooter& player_shooting, int& current_bullets, Map& map);
};
#endif  // WOLFENSTEIN_TALLER1_GUN_H
