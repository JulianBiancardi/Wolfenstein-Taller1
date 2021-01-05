#include "event_building.h"

Event build_move_event(int player_id, Point where) {
  PointData point = {.x = where.getX(), .y = where.getY()};
  Event event = {.type = 1, .player_id = player_id, .data={.point = point}};

  return event;
}

Event build_grab_event(int player_id, int what) {
  Event event = {.type = 2, .player_id = player_id, .data={.item = what}};

  return event;
}
