#include "shoot_handler.h"

ShootHandler::ShootHandler(Player& who, Player* enemy_shot, double damage_done)
    : who(who), enemy_shot(enemy_shot), damage_done(damage_done) {}

void ShootHandler::handle(Match& match, CollisionChecker& checker) {
}
