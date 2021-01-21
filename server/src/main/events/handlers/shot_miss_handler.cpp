#include "shot_miss_handler.h"
#include "../../game/match.h"

ShotMissHandler::ShotMissHandler(Player& who, int bullets)
    : who(who), bullets_shot(bullets) {}

void ShotMissHandler::handle(Match& match, CollisionChecker& checker) {
  who.decrease_bullets(bullets_shot);

  consequence_grab_event(match, checker, who);
}
