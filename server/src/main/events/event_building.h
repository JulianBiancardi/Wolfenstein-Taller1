#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_

#include "event.h"
#include "../../../../common/src/main/utils/point.h"

Event build_move_event(int player_id, Point where);
Event build_grab_event(int player_id, int what);

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_EVENTS_EVENT_BUILDING_H_
