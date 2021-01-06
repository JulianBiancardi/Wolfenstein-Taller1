#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_

#include "../../../../common/src/main/events/event_info.h"
#include "../../../../common/src/main/utils/point.h"

// Used to get result event structs
Event build_move_event(int player_id, Point where);
Event build_grab_event(int player_id, int what);

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_
