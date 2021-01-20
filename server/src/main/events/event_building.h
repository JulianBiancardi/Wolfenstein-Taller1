#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_

#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/utils/point.h"

// Used to get result event structs
packet_t build_move_event(int player_id, Point where);
packet_t build_grab_event(int player_id, int what);
packet_t build_damage_event(int player_id, double damage);
packet_t build_change_gun_event(int player_id, int gun);
packet_t build_kill_event(int killed, int killer);
packet_t build_game_over_event();

#endif  // WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_
