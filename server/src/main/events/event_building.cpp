#include "event_building.h"

packet_t build_move_packet(int player_id, int direction) {
  packet_t event = {.type = MOVE_PACKET,
      .player_id = player_id,
      .data = {.direction = direction}};

  return event;
}

packet_t build_rotation_packet(int player_id, int direction) {
  packet_t event = {.type = ROTATE_PACKET,
      .player_id = player_id,
      .data = {.direction = direction}};

  return event;
}

packet_t build_grab_packet(int player_id, int what_id) {
  packet_t event = {.type = GRAB_PACKET,
      .player_id = player_id,
      .data = {.item = what_id}};

  return event;
}

packet_t build_door_packet(int player_id, int door_id) {
  packet_t event = {.type = DOOR_PACKET,
      .player_id = player_id,
      .data = {.door_id = door_id}};

  return event;
}

packet_t build_change_gun_packet(int player_id, int gun) {
  packet_t event = {.type = CHANGE_GUN_PACKET,
      .player_id = player_id,
      .data = {.gun = gun}};

  return event;
}

packet_t build_damage_packet(int player_id, int damage, int enemy_shot) {
  DamageData shot = {.damage_done = damage, .enemy_shot = enemy_shot};
  packet_t event = {.type = DAMAGE_PACKET,
      .player_id = player_id,
      .data = {.shot = shot}};

  return event;
}

packet_t build_game_over_packet() {
  packet_t event = {.type = GAME_OVER_PACKET};

  return event;
}
