#include "move_handler.h"
#include "../game/match.h"
#include "event_building.h"

MoveHandler::MoveHandler(Player &who, Point where) : who(who), where(where) {}

void MoveHandler::handle(Match &match, CollisionChecker &checker) {
  if (checker.can_move(where, who))
    who.set_position(where);

  match.enqueue_result(build_move_event(match.get_player_id(who),
                                        who.get_position()));
}
