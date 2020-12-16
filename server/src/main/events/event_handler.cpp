#include "event_handler.h"
#include "event_building.h"
#include "../game/match.h"
#include "../game/sprites/items/items.h"

void EventHandler::consequence_grab_event(Match &match,
                                          CollisionChecker &checker,
                                          Player &who) {
  try { //IS USING EXCEPTION OK?
    Items *grabbed = checker.grabbed_item(who);
    grabbed->use(who);
    int item_id = match.get_item_id(grabbed);
    int player_id = match.get_player_id(who);
    match.enqueue_result(build_grab_event(player_id, item_id));
  } catch (...) {} //TODO Use custom exception
}
