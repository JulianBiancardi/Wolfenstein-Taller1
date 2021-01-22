#include "event_handler_builder.h"
#include "handlers/move_handler.h"
#include "handlers/damage_handler.h"
#include "handlers/change_gun_handler.h"
#include "handlers/game_over_handler.h"

Player& EventHandlerBuilder::get_doer(const packet_t& event,
                                      std::unordered_map
                                          <int, Player>& players) {
  return players.at(event.player_id);
}

EventHandler* move_handler(Player& who, const packet_t& event) {
  return new MoveHandler(who, event.data.direction);
}

EventHandler* rotate_handler(Player& who, const packet_t& event) {
  return nullptr; // TODO
}

EventHandler* door_interaction_handler(const packet_t& event) {
  return nullptr; // TODO
}

EventHandler* change_gun_handler(Player& who, const packet_t& event) {
  return new ChangeGunHandler(who, event.data.gun);
}

EventHandler* damage_handler(Player& who,
                             Player* enemy_hit,
                             const packet_t& event) {
  return new DamageHandler(who, enemy_hit, event.data.shot.damage_done);
}

EventHandler* game_over_handler() {
  return new GameOverHandler();
}

EventHandler* EventHandlerBuilder::build(const packet_t& event,
                                         std::unordered_map
                                             <int, Player>& players) {
  switch (event.type) {
    case MOVE_PACKET: return move_handler(get_doer(event, players), event);
    case ROTATE_PACKET: return rotate_handler(get_doer(event, players), event);
    case DOOR_PACKET: return door_interaction_handler(event);
    case CHANGE_GUN_PACKET:
      return change_gun_handler(get_doer(event, players),
                                event);
    case DAMAGE_PACKET: {
      if (event.data.shot.enemy_shot == INVALID_ID)
        return damage_handler(get_doer(event, players), nullptr, event);
      else
        return damage_handler(get_doer(event, players),
                              &players.at(event.data.shot.enemy_shot),
                              event);
    }
    case GAME_OVER_PACKET: return game_over_handler();
    default: throw -1; //TODO Throw ours exception
  }
}
