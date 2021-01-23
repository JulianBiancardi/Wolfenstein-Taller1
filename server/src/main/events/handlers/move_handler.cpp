#include "move_handler.h"
#include "../../game/match.h"
#include "../event_building.h"

MoveHandler::MoveHandler(Player& who, int direction)
    : who(who), direction(direction) {}

void MoveHandler::handle(Match& match, CollisionChecker& checker) {
  Point where = who.next_position(direction);

  if (checker.can_move(where, who)) {
    who.set_position(where);
    match.enqueue_result_for_all(build_move_packet(who.get_id(), direction));
    consequence_grab_event(match, checker, who);
  } else {
    match.enqueue_result_for_all(build_move_packet(who.get_id(), INVALID));
  }
}
