#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HIT_HANDLER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HIT_HANDLER_H_

#include "event_handler.h"
#include "../game/collision_checker.h"

class ShotHitHandler : public EventHandler {
 private:
  Player& who; // TODO Should not be player, bots also shoot
  Player& enemy_shot; // TODO Should not be player, bots also get shot
  double damage_done; // Could be float
  int bullets_shot;

 public:
  ShotHitHandler(Player& who, Player& enemy, double damage, int bullets);

  void handle(Match& match, CollisionChecker& checker);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HIT_HANDLER_H_
