#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_MOVE_HANDLER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_MOVE_HANDLER_H_

#include "event_handler.h"

class MoveHandler : public EventHandler {
 private:
  Player& who;
  int direction;

 public:
  MoveHandler(Player& who, int direction);
  void handle(Match& match, CollisionChecker& checker);
};

#endif  // WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_MOVE_HANDLER_H_
