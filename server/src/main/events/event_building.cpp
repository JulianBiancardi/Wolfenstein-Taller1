#include "event_building.h"

packet_t build_move_event(int player_id, Point where) {
  PointData point = {.x = where.getX(), .y = where.getY()};
  packet_t event = {.type = MOVE_PACKET,
      .player_id = player_id,
      .data = {.point = point}};

  return event;
}

packet_t build_grab_event(int player_id, int what) {
  packet_t event = {.type = GRAB_PACKET,
      .player_id = player_id,
      .data = {.item = what}};

  return event;
}

packet_t build_damage_event(int player_id, double damage) {
  packet_t event = {.type = DAMAGE_PACKET,
      .player_id = player_id,
      .data = {.damage = damage}};

  return event;
}

packet_t build_change_gun_event(int player_id, int gun) {
  packet_t event = {.type = CHANGE_GUN_PACKET,
      .player_id = player_id,
      .data = {.gun = gun}};

  return event;
}

packet_t build_kill_event(int killed, int killer) {
  packet_t event = {.type = KILL_PACKET,
      .player_id = killed,
      .data = {.killer = killer}};

  return event;
}

packet_t build_game_over_event() {
  packet_t event = {.type = GAME_OVER_PACKET};

  return event;
}
