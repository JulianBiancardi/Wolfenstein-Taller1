#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_HANDLER_BUILDER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_HANDLER_BUILDER_H_

#include <unordered_map>

#include "../../../../common/src/main/utils/point.h"
#include "handlers/event_handler.h"

class EventHandlerBuilder {
 private:
  Player& get_doer(const packet_t& event,
                   std::unordered_map<int, Player>& players);

 public:
  EventHandler* build(const packet_t& event,
                      std::unordered_map<int, Player>& players);
};

#endif  // WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_HANDLER_BUILDER_H_
