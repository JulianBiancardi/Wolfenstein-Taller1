#include "damage_handler.h"
#include "../../game/match.h"
#include "../event_building.h"

DamageHandler::DamageHandler(Player& who, Player* enemy, int damage)
    : who(who), enemy_shot(enemy), damage_done(damage) {}

bool DamageHandler::shot_hits_enemy() { return enemy_shot != nullptr; }

void DamageHandler::damage_enemy(Match& match, CollisionChecker& checker) {
  enemy_shot->receive_damage(damage_done);
  match.enqueue_result_for_all(build_damage_packet(who.get_id(),
                                                   damage_done,
                                                   enemy_shot->get_id()));
  if (enemy_shot->is_dead()) {
    match.get_map().add_drop(*enemy_shot);
    who.add_kill();
    if (enemy_shot->has_lives_left())
      enemy_shot->respawn();
    else
      match.eliminate_player(enemy_shot->get_id());
  } else {
    consequence_grab_event(match, checker, *enemy_shot);
  } // If a player gets killed over a kit int won't grab it.
}

void DamageHandler::handle(Match& match, CollisionChecker& checker) {
  who.shoot();

  if (shot_hits_enemy())
    damage_enemy(match, checker);

  consequence_grab_event(match, checker, who);
}

