#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_MOVE_HANDLER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_MOVE_HANDLER_H_

#include "../../../../../common/src/main/utils/point.h"
#include "../../game/collision_checker.h"
#include "event_handler.h"

class MoveHandler : public EventHandler {
 private:
  Player &who;
  Point where;

 public:
  MoveHandler(Player &who, Point where);

  void handle(Match &match, CollisionChecker &checker);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_MOVE_HANDLER_H_
