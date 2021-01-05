#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_HANDLER_BUILDER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_HANDLER_BUILDER_H_

#include "event_handler.h"
#include "../../../../common/src/main/utils/point.h"
#include <unordered_map>

class EventHandlerBuilder {
 private:
  Player &get_doer(const Event &event,
                   std::unordered_map<int, Player> &players);
  EventHandler *move_event(Player &doer, double x, double y);

 public:
  EventHandler *build(const Event &event,
                      std::unordered_map<int, Player> &players);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_HANDLER_BUILDER_H_
