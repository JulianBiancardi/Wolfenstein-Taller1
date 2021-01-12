#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_HANDLER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_HANDLER_H_

#include "../../../../common/src/main/packets/packet.h"
#include "../game/collision_checker.h"

class Match;

class EventHandler {
 public:
  virtual void handle(Match &match, CollisionChecker &checker) = 0;
  void consequence_grab_event(Match &match, CollisionChecker &checker,
                              Player &who);  // Possibly not necessary
};

#endif  // WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_HANDLER_H_
