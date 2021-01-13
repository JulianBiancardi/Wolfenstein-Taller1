#include "shoot_hit_handler.h"

ShootHitHandler::ShootHitHandler(Player& who, Player& enemy, double damage)
    : who(who), enemy_shot(enemy), damage_done(damage) {}

void ShootHitHandler::handle(Match& match, CollisionChecker& checker) {
}

