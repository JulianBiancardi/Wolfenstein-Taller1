#include "shoot_hit_handler.h"
#include "../game/match.h"
#include "event_building.h"

ShootHitHandler::ShootHitHandler(Player& who,
                                 Player& enemy,
                                 double damage,
                                 int bullets)
    : who(who), enemy_shot(enemy), damage_done(damage), bullets_shot(bullets) {}

void ShootHitHandler::handle(Match& match, CollisionChecker& checker) {
  who.shoot(enemy_shot, damage_done, bullets_shot);

  match.enqueue_result(build_damage_event(enemy_shot.get_id(), damage_done),
                       enemy_shot.get_id());

  consequence_grab_event(match, checker, who);
  consequence_grab_event(match, checker, enemy_shot);
}

