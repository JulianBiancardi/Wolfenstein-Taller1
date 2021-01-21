#include "move_handler.h"
#include "../../game/match.h"
#include "../event_building.h"

MoveHandler::MoveHandler(Player& who, Point where) : who(who), where(where) {}

void MoveHandler::handle(Match& match, CollisionChecker& checker) {
  if (checker.can_move(where, who)) {
    who.set_position(where);
    consequence_grab_event(match, checker, who);
  } // Grab event is enqueued before move event!

  match.enqueue_result_for_all(build_move_event(who.get_id(),
                                                who.get_position()));
}
