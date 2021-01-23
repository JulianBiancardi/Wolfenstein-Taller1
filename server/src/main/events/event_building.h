#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_

#include "../../../../common/src/main/packets/packet.h"

// Used to get result packets structs
packet_t build_move_packet(int player_id, int direction);
packet_t build_rotation_packet(int player_id, int direction);
packet_t build_grab_packet(int player_id, int what_id);
packet_t build_door_packet(int player_id, int door_id);
packet_t build_change_gun_packet(int player_id, int gun);
packet_t build_damage_packet(int player_id, int damage, int enemy_shot);
packet_t build_game_over_packet();

#endif  // WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_
