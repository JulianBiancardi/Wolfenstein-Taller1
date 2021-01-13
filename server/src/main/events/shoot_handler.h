#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HANDLER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HANDLER_H_

#include "event_handler.h"
#include "../game/collision_checker.h"

class ShootHandler : public EventHandler {
 private:
  Player& who; // TODO Should not be player, bots also shoot
  int bullets_shot;

 public:
  ShootHandler(Player& who, int bullets);

  void handle(Match& match, CollisionChecker& checker);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HANDLER_H_
