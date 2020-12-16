#include "event_handler_builder.h"
#include "move_handler.h"

Player &EventHandlerBuilder::get_doer(const Event &event,
                                      std::unordered_map
                                          <int, Player> &players) {
  return players.at(event.player_id);
}

EventHandler *EventHandlerBuilder::move_event(Player &doer,
                                              double x,
                                              double y) {
  return new MoveHandler(doer, Point(x, y));
}

EventHandler *EventHandlerBuilder::build(const Event &event,
                                         std::unordered_map
                                             <int, Player> &players) {
  Player &doer = get_doer(event, players);

  switch (event.type) {
    case 1: //TODO Use constants
      return move_event(doer, event.data.point.x, event.data.point.y);
      break;

    default: throw -1; //TODO Throw ours exception
  }
}
