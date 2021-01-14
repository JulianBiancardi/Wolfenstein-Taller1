#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_CHANGE_GUN_HANDLER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_CHANGE_GUN_HANDLER_H_

#include "event_handler.h"
#include "../game/collision_checker.h"

class ChangeGunHandler : public EventHandler {
 private:
  Player& who;
  int gun;

 public:
  ChangeGunHandler(Player& who, int gun);

  void handle(Match& match, CollisionChecker& checker);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_CHANGE_GUN_HANDLER_H_
