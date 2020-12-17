#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_SHOOTER_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_SHOOTER_H_

#include "../../../../common/src/main/utils/ray.h"
//#include "../../ray_casting.h"
#include "collisions/circle_mask.h"
#include "guns/gun.h"
#include "randomizer.h"
#include "sprites/sprite.h"

class Player;

// TODO Possible inheritance from identifiable
class Shooter {
 protected:
  Ray angled_position;
  double angle;
  // Map &map;
  // Circle_mask mask;

 public:
  Shooter(Point origin, double angle);
  ~Shooter() {}
  //  void shoot_checker();
  void shoot(Gun &gun);
  virtual void shoot_player(Player &shot_player, Gun &gun);
};

#endif  // WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_SHOOTER_H_
