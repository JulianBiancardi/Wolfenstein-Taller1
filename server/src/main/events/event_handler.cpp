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
    int item_id = grabbed->get_id();
    int player_id = who.get_id();
    match.enqueue_result(build_grab_event(player_id, item_id));
    delete grabbed;
    match.get_map().get_items().erase(item_id);
  } catch (...) {} //TODO Use custom exception
}
