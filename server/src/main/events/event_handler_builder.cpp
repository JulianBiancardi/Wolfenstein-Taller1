#include "event_handler_builder.h"
#include "move_handler.h"
#include "shot_miss_handler.h"
#include "shot_hit_handler.h"
#include "change_gun_handler.h"

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

  //TODO Use constants
  switch (event.type) {
    case 1: return move_event(doer, event.data.point.x, event.data.point.y);
    case 3: {
      int bullets_shot = event.data.shot.bullets_shot;
      Player& enemy_hit = players.at(event.data.shot.enemy_shot);
      double damage_done = event.data.shot.damage_done;
      return new ShotHitHandler(doer, enemy_hit, damage_done, bullets_shot);
    }
    case 5: return new ChangeGunHandler(doer, event.data.gun);
    case 6: return new ShotMissHandler(doer, event.data.bullets_shot);
    default: throw -1; //TODO Throw ours exception
  }
}
