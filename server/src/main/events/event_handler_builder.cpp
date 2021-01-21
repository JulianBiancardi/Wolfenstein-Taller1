#include "event_handler_builder.h"
#include "handlers/move_handler.h"
#include "handlers/shot_miss_handler.h"
#include "handlers/shot_hit_handler.h"
#include "handlers/change_gun_handler.h"
#include "handlers/game_over_handler.h"

Player& EventHandlerBuilder::get_doer(const packet_t& event,
                                      std::unordered_map
                                          <int, Player>& players) {
  return players.at(event.player_id);
}

EventHandler* move_handler(Player& who, const packet_t& event) {
  return new MoveHandler(who, Point(event.data.point.x, event.data.point.y));
}

EventHandler* shot_hit_handler(Player& who,
                               Player& enemy_hit,
                               const packet_t& event) {
  int bullets_shot = event.data.shot.bullets_shot;
  double damage_done = event.data.shot.damage_done;
  return new ShotHitHandler(who, enemy_hit, damage_done, bullets_shot);
}

EventHandler* shot_miss_handler(Player& who, const packet_t& event) {
  return new ShotMissHandler(who, event.data.bullets_shot);
}

EventHandler* change_gun_handler(Player& who, const packet_t& event) {
  return new ChangeGunHandler(who, event.data.gun);
}

EventHandler* game_over_handler() {
  return new GameOverHandler();
}

EventHandler* EventHandlerBuilder::build(const packet_t& event,
                                         std::unordered_map
                                             <int, Player>& players) {
  switch (event.type) {
    case MOVE_PACKET: return move_handler(get_doer(event, players), event);
    case SHOT_HIT_PACKET:
      return shot_hit_handler(get_doer(event, players),
                              players.at(event.data.shot.enemy_shot),
                              event);
    case CHANGE_GUN_PACKET:
      return change_gun_handler(get_doer(event, players),
                                event);
    case SHOT_MISS_PACKET:
      return shot_miss_handler(get_doer(event, players),
                               event);
    case GAME_OVER_PACKET: return game_over_handler();
    default: throw -1; //TODO Throw ours exception
  }
}
