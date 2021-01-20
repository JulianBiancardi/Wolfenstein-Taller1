#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_GAME_OVER_HANDLER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_GAME_OVER_HANDLER_H_

#include "event_handler.h"

class GameOverHandler : public EventHandler {
 public:
  GameOverHandler();

  void handle(Match& match, CollisionChecker& checker);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_GAME_OVER_HANDLER_H_
