#include "change_gun_handler.h"
#include "../game/match.h"
#include "event_building.h"

ChangeGunHandler::ChangeGunHandler(Player& who, int gun)
    : who(who), gun(gun) {}

void ChangeGunHandler::handle(Match& match, CollisionChecker& checker) {
  who.change_gun(gun);

  match.enqueue_result_for_all_others(build_change_gun_event(who.get_id(), gun),
                                      who.get_id());
}
