#include "rotate_handler.h"
#include "../../game/match.h"
#include "../event_building.h"

RotateHandler::RotateHandler(Player& who, int direction)
    : who(who), direction(direction) {}

void RotateHandler::handle(Match& match, CollisionChecker& checker) {
  who.rotate(direction);

  match.enqueue_result_for_all(build_rotation_packet(who.get_id(), direction));
}
