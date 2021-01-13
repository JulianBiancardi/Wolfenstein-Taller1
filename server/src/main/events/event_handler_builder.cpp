#include "event_handler_builder.h"
#include "move_handler.h"
#include "shoot_handler.h"
#include "shoot_hit_handler.h"

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
      int bullets_shot = event.data.shot.bullets_shot;
      if (event.data.shot.enemy_shot != -1) { // TODO Use constant
        Player& enemy_hit = players.at(event.data.shot.enemy_shot); // HIT
        double damage_done = event.data.shot.damage_done;
        return new ShootHitHandler(doer, enemy_hit, damage_done, bullets_shot);
      } else {
        return new ShootHandler(doer, bullets_shot); // Miss
      }
    }
    default: throw -1; //TODO Throw ours exception
  }
}
