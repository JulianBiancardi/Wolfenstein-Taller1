#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_HANDLERS_ROTATE_HANDLER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_HANDLERS_ROTATE_HANDLER_H_

#include "event_handler.h"

class RotateHandler : public EventHandler {
 private:
  Player& who;
  int direction;

 public:
  RotateHandler(Player& who, int direction);
  void handle(Match& match, CollisionChecker& checker);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_HANDLERS_ROTATE_HANDLER_H_
