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

EventHandler* move_event(Player& who, const packet_t& event) {
  return new MoveHandler(who, Point(event.data.point.x, event.data.point.y));
}

EventHandler* shot_hit_event(Player& who,
                             Player& enemy_hit,
                             const packet_t& event) {
  int bullets_shot = event.data.shot.bullets_shot;
  double damage_done = event.data.shot.damage_done;
  return new ShotHitHandler(who, enemy_hit, damage_done, bullets_shot);
}

EventHandler* shot_miss_event(Player& who, const packet_t& event) {
  return new ShotMissHandler(who, event.data.bullets_shot);
}

EventHandler* change_gun_event(Player& who, const packet_t& event) {
  return new ChangeGunHandler(who, event.data.gun);
}

EventHandler* EventHandlerBuilder::build(const packet_t& event,
                                         std::unordered_map
                                             <int, Player>& players) {
  Player& doer = get_doer(event, players);

  //TODO Use constants
  switch (event.type) {
    case 1: return move_event(doer, event);
    case 3:
      return shot_hit_event(doer,
                            players.at(event.data.shot.enemy_shot).event);
    case 5: return change_gun_event(doer, event);
    case 6: return shot_miss_event(doer, event);
    default: throw -1; //TODO Throw ours exception
  }
}
