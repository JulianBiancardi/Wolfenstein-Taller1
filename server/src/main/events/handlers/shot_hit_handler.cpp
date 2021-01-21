#include "shot_hit_handler.h"
#include "../../game/match.h"
#include "../event_building.h"

ShotHitHandler::ShotHitHandler(Player& who,
                               Player& enemy,
                               double damage,
                               int bullets)
    : who(who), enemy_shot(enemy), damage_done(damage), bullets_shot(bullets) {}

void ShotHitHandler::handle(Match& match, CollisionChecker& checker) {
  who.shoot(enemy_shot, damage_done, bullets_shot);

  if (enemy_shot.is_dead()) {
    match.get_map().add_drop(enemy_shot);
    who.add_kill();
    if (enemy_shot.has_lives_left())
      enemy_shot.respawn();
    else
      match.eliminate_player(enemy_shot.get_id());
    match.enqueue_result_for_all(build_kill_event(enemy_shot.get_id(),
                                                  who.get_id()));
  } else {
    match.enqueue_result(build_damage_event(enemy_shot.get_id(), damage_done),
                         enemy_shot.get_id());

    consequence_grab_event(match, checker, enemy_shot);
  } // If a player gets killed over a kit int won't grab it.

  consequence_grab_event(match, checker, who);
}

