#include "event_handler_builder.h"
#include "move_handler.h"
#include "shoot_handler.h"

Player& EventHandlerBuilder::get_doer(const packet_t& event,
                                      std::unordered_map
                                          <int, Player>& players) {
  return players.at(event.player_id);
}

// TODO Remake
EventHandler* EventHandlerBuilder::move_event(Player& doer,
                                              double x,
                                              double y) {
  return new MoveHandler(doer, Point(x, y));
}

EventHandler* EventHandlerBuilder::build(const packet_t& event,
                                         std::unordered_map
                                             <int, Player>& players) {
  Player& doer = get_doer(event, players);

  switch (event.type) {
    case 1: //TODO Use constants
      return move_event(doer, event.data.point.x, event.data.point.y);
    case 3: { //TODO Use constants
      Player* enemy_shot = nullptr;
      if (event.data.shot.enemy_shot != -1) { // TODO Use constant
        enemy_shot = &players.at(event.data.shot.enemy_shot);
      }
      return new ShootHandler(doer, enemy_shot, event.data.shot.damage_done);
    }
    default: throw -1; //TODO Throw ours exception
  }
}
