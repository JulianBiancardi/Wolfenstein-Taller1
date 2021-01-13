#include "shoot_handler.h"
#include "../game/match.h"

ShootHandler::ShootHandler(Player& who, int bullets)
    : who(who), bullets_shot(bullets) {}

void ShootHandler::handle(Match& match, CollisionChecker& checker) {
  who.decrease_bullets_2(bullets_shot);
}
