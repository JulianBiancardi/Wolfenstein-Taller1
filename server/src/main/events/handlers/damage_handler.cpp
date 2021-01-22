#include "damage_handler.h"
#include "../../game/match.h"
#include "../event_building.h"

DamageHandler::DamageHandler(Player& who, Player* enemy, int damage)
    : who(who), enemy_shot(enemy), damage_done(damage) {}

void DamageHandler::handle(Match& match, CollisionChecker& checker) {
  who.shoot();

  if (enemy_shot != nullptr) {
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

  consequence_grab_event(match, checker, who);
}

