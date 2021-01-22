#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HIT_HANDLER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HIT_HANDLER_H_

#include "event_handler.h"

class DamageHandler : public EventHandler {
 private:
  Player& who;
  Player* enemy_shot;
  int damage_done;

 public:
  DamageHandler(Player& who, Player* enemy, int damage);

  void handle(Match& match, CollisionChecker& checker);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_SHOOT_HIT_HANDLER_H_
