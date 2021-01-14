#include "event_building.h"

packet_t build_move_event(int player_id, Point where) {
  PointData point = {.x = where.getX(), .y = where.getY()};
  packet_t event = {.type = 1,
      .player_id = player_id,
      .data = {.point = point}};

  return event;
}

packet_t build_grab_event(int player_id, int what) {
  packet_t event = {.type = 2, .player_id = player_id, .data = {.item = what}};

  return event;
}

packet_t build_damage_event(int player_id, double damage) {
  packet_t event = {.type = 4,
      .player_id = player_id,
      .data = {.damage = damage}};

  return event;
}

packet_t build_change_gun_event(int player_id, int gun) {
  packet_t event = {.type = 5, .player_id = player_id, .data = {.gun = gun}};

  return event;
}
