#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HANDLER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HANDLER_H_

#include "event_handler.h"
#include "../game/collision_checker.h"

class ShootHandler : public EventHandler {
 private:
  Player& who; // TODO Should not be player, bots also shoot
  // It's a pointer, it can be NULL
  Player* enemy_shot; // TODO Should not be player, bots also get shot
  double damage_done; // Could be float

 public:
  ShootHandler(Player& who, Player* enemy_shot, double damage_done);

  void handle(Match& match, CollisionChecker& checker);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HANDLER_H_
