#include "match_tests.h"

#include "../../../common/src/tests/tests_setup.h"
#include "../main/managers/match.h"
#include "../../../common/src/main/ids/gun_ids.h"
#include "client_mock.h"

#define MOVEMENT_MAP "test_map_movement"
#define ITEMS_MAP "test_map_items"
#define ROCKET_MAP "test_map_rocket"

int static can_move_up_player();
int static can_move_up_player_two_times();
int static can_move_up_until_wall();
int static grabs_medic_kit_and_restores_all_health();
int static grabs_medic_kit_and_restores_health_correctly();
int static grabs_blood_only_when_health_is_less_than_eleven();
int static medic_kit_disappears_after_grabbing_it();
int static player_shoots_enemy();
int static player_shoots_nobody();
int static player_shoots_enemy_over_blood_and_grabs_it();
int static player_grabs_bullets();
int static player_changes_gun();
int static player_kills_enemy_and_it_respawns();
int static player_kills_enemy_and_it_is_no_longer_in_the_map();
int static player_cannot_grab_gun();
int static player_kills_enemy_and_grabs_drop();
int static player_grabs_point_items();
int static rocket_spawns_where_it_should();
int static rocket_moves_once_correctly();
int static rocket_moves_until_it_finds_a_player();
int static rocket_explodes_and_damages_player();
int static rocket_explodes_and_damages_multiple_players();

void match_tests() {
  begin_tests("MATCH");

  print_test("Un jugador en una partida se mueve correctamente",
             can_move_up_player, NO_ERROR);
  print_test("Un jugador se mueve dos veces", can_move_up_player_two_times,
             NO_ERROR);
  print_test("Se mueve un jugador hasta que llega a la pared",
             can_move_up_until_wall, NO_ERROR);
  print_test("Jugador se mueve, agarra kit medico y recupera toda la salud",
             grabs_medic_kit_and_restores_all_health, NO_ERROR);
  print_test("Jugador se mueve, agarra kit medico y recupera salud",
             grabs_medic_kit_and_restores_health_correctly, NO_ERROR);
  print_test("Jugador agarra la sangre solo cuando tiene menos de 11 de vida",
             grabs_blood_only_when_health_is_less_than_eleven, NO_ERROR);
  print_test("El kit medico desaparece al agarrarse",
             medic_kit_disappears_after_grabbing_it, NO_ERROR);
  print_test("Jugador dispara correctamente a otro", player_shoots_enemy,
             NO_ERROR);
  print_test("Jugador dispara pero no acierta", player_shoots_nobody, NO_ERROR);
  print_test("Jugador recibe disparo y agarra sangre",
             player_shoots_enemy_over_blood_and_grabs_it, NO_ERROR);
  print_test("Jugador agarra balas", player_grabs_bullets, NO_ERROR);
  print_test("Jugador cambia de arma correctamente", player_changes_gun,
             NO_ERROR);
  print_test("Jugador mata enemigo y respawnea",
             player_kills_enemy_and_it_respawns, NO_ERROR);
  print_test("Enemigo muere definitivamente y desaparece",
             player_kills_enemy_and_it_is_no_longer_in_the_map, NO_ERROR);
  print_test("Jugador no puede agarrar arma que ya tiene",
             player_cannot_grab_gun, NO_ERROR);
  print_test("Jugador agarra drop de muerte de otro",
             player_kills_enemy_and_grabs_drop, NO_ERROR);
  print_test("Jugador agarra items de puntos y se le suman",
             player_grabs_point_items, NO_ERROR);
  print_test("El cohete aparece donde debe", rocket_spawns_where_it_should,
             NO_ERROR);
  print_test("El cohete se mueve una vez", rocket_moves_once_correctly,
             NO_ERROR);
  print_test("El cohete se mueve hasta colisionar con un jugador",
             rocket_moves_until_it_finds_a_player, NO_ERROR);
  print_test("Jugador se daña al explotar un cohete",
             rocket_explodes_and_damages_player, NO_ERROR);
  print_test("Un cohete daña multiples jugadores",
             rocket_explodes_and_damages_multiple_players, NO_ERROR);

  end_tests();
}

int static can_move_up_player() {
  std::string map_name(MOVEMENT_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  Point initial_position = match.get_players().at(1).get_position();

  match.move_player(1, UP);

  Point final_position = match.get_players().at(1).get_position();

  match.end();

  if (double_compare(final_position.getX(),
                     initial_position.getX() + CL::player_speed)
      && initial_position.getY() == final_position.getY())
    return NO_ERROR;

  return ERROR;
}

int static can_move_up_player_two_times() {
  std::string map_name(MOVEMENT_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  Point initial_position = match.get_players().at(1).get_position();

  match.move_player(1, UP);
  match.move_player(1, UP);

  Point final_position = match.get_players().at(1).get_position();

  match.end();

  if (double_compare(final_position.getX(),
                     initial_position.getX() + 2 * CL::player_speed)
      && initial_position.getY() == final_position.getY())
    return NO_ERROR;

  return ERROR;
}

int static can_move_up_until_wall() {
  std::string map_name(MOVEMENT_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  unsigned int movements_made = 0;

  Point initial_position = match.get_players().at(1).get_position();

  while (match.move_player(1, UP)) movements_made++;

  Point final_position = match.get_players().at(1).get_position();

  match.end();

  if (double_compare(final_position.getX(),
                     initial_position.getX()
                         + movements_made * CL::player_speed)
      && initial_position.getY() == final_position.getY())
    return NO_ERROR;

  return ERROR;
}

int static grabs_medic_kit_and_restores_all_health() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  match.end();

  if (match.get_players().at(1).is_full_health())
    return NO_ERROR;

  return ERROR;
}

int static grabs_medic_kit_and_restores_health_correctly() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  match.shoot_gun(2, 1, CL::medic_kit_health_recovered + 1);

  // Walks until wall
  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  match.end();

  if (match.get_players().at(1).get_health() == CL::player_health - 1)
    return NO_ERROR;

  return ERROR;
}

int static grabs_blood_only_when_health_is_less_than_eleven() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  for (int i = 0; i < 1 / CL::player_speed; i++) {
    match.move_player(1, RIGHT);
  }

  // Walks until wall
  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  match.shoot_gun(2, 1, CL::player_health - 10);

  if (match.get_players().at(1).get_health() != 10)
    return ERROR;

  // Walks until blood
  while (match.move_player(1, DOWN) && match.grab_item(1) == 0);

  match.end();

  if (match.get_players().at(1).get_health() == 10 + CL::blood_health_recovered)
    return NO_ERROR;

  return ERROR;
}

int static medic_kit_disappears_after_grabbing_it() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  match.shoot_gun(2, 1, CL::player_health - 5);

  // Walks until wall
  while (match.move_player(1, UP)) { match.grab_item(1); }

  if (match.get_players().at(1).get_health()
      != 5 + CL::medic_kit_health_recovered)
    return ERROR;

  // Walks until medic kit
  while (match.move_player(1, DOWN) && match.grab_item(1) == 0);

  match.end();

  if (match.get_players().at(1).get_health()
      == 5 + CL::medic_kit_health_recovered)
    return NO_ERROR;

  return ERROR;
}

int static player_shoots_enemy() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  match.shoot_gun(2, 1, CL::player_health - 5);

  if (match.get_players().at(1).get_health() != 5)
    return ERROR;

  if (match.get_players().at(2).get_bullets()
      != CL::player_bullets - CL::pistol_bullet_required)
    return ERROR;

  match.end();

  return NO_ERROR;
}

int static player_shoots_nobody() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  match.shoot_gun(1, 0, 5);

  if (match.get_players().at(1).get_health() != CL::player_health)
    return ERROR;

  if (match.get_players().at(1).get_bullets()
      != CL::player_bullets - CL::pistol_bullet_required)
    return ERROR;

  match.end();

  return NO_ERROR;
}

int static player_shoots_enemy_over_blood_and_grabs_it() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  for (int i = 0; i < 1 / CL::player_speed; i++) {
    match.move_player(1, RIGHT);
  }

  while (match.get_players().at(1).get_position().getX() < 7.5) {
    match.move_player(1, UP);
    match.grab_item(1);
  }

  if (match.get_players().at(1).get_health() != CL::player_health)
    return ERROR;

  match.shoot_gun(2, 1, CL::player_health - 5);

  if (match.get_players().at(1).get_health() != 5)
    return ERROR;

  if (match.grab_item(1) == 0)
    return ERROR;

  if (match.get_players().at(1).get_health() != 5 + CL::blood_health_recovered)
    return ERROR;

  if (match.get_players().at(2).get_bullets()
      != CL::player_bullets - CL::pistol_bullet_required)
    return ERROR;

  match.end();

  return NO_ERROR;
}

int static player_grabs_bullets() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  for (int i = 0; i < 2 / CL::player_speed; i++) {
    match.move_player(1, RIGHT);
  }

  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  if (match.get_players().at(1).get_bullets()
      != CL::player_bullets + CL::bullets_amount)
    return ERROR;

  match.end();

  return NO_ERROR;
}

int static player_changes_gun() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  for (int i = 0; i < 1 / CL::player_speed; i++) {
    match.move_player(1, LEFT);
  }

  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  if (!match.get_players().at(1).has_gun(MACHINE_GUN_ID))
    return ERROR;

  if (!match.change_gun(1, MACHINE_GUN_ID))
    return ERROR;

  if (match.get_players().at(1).get_active_gun() != MACHINE_GUN_ID)
    return ERROR;

  match.end();

  return NO_ERROR;
}

int static player_kills_enemy_and_it_respawns() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  Point initial_position = match.get_players().at(2).get_position();

  for (int i = 0; i < 1 / CL::player_speed; i++) {
    match.move_player(2, LEFT);
  }

  match.shoot_gun(1, 2, CL::player_health + 1);

  match.end();

  if (match.get_players().at(2).get_position() == initial_position)
    return NO_ERROR;

  return ERROR;
}

int static player_kills_enemy_and_it_is_no_longer_in_the_map() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  for (int i = 0; i < CL::player_lives; i++) {
    match.shoot_gun(1, 2, CL::player_health + 1);
  }

  while (match.move_player(1, RIGHT));

  if (!double_compare(match.get_players().at(1).get_position().getY(),
                      10 - 1 - CL::player_mask_radio))
    return ERROR;

  match.end();

  if (match.get_players().size() == 1)
    return NO_ERROR;

  return ERROR;
}

int static player_cannot_grab_gun() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  for (int i = 0; i < 1 / CL::player_speed; i++) {
    match.move_player(1, LEFT);
  }

  if (match.get_players().at(1).has_gun(MACHINE_GUN_ID))
    return ERROR;

  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  if (!match.get_players().at(1).has_gun(MACHINE_GUN_ID))
    return ERROR;

  while (match.move_player(1, UP)) {
    if (match.grab_item(1) != 0)
      return ERROR;
  }

  match.end();

  return NO_ERROR;
}

int static player_kills_enemy_and_grabs_drop() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  Point initial_position = match.get_players().at(2).get_position();

  while (match.move_player(2, DOWN) && match.grab_item(2) == 0);
  while (match.move_player(2, DOWN) && match.grab_item(2) == 0);

  match.change_gun(2, MACHINE_GUN_ID);

  while (match.get_players().at(2).get_position() != initial_position) {
    match.move_player(2, UP);
  }

  for (int i = 0; i < 2 / CL::player_speed; i++) {
    match.move_player(2, LEFT);
  }

  match.kill_player(2);

  while (match.move_player(1, RIGHT) && match.grab_item(1) == 0);
  while (match.move_player(1, DOWN) && match.grab_item(1) == 0);
  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  if (!match.get_players().at(1).has_keys())
    return ERROR;

  if (!match.get_players().at(1).has_gun(MACHINE_GUN_ID))
    return ERROR;

  if (match.get_players().at(1).get_bullets()
      != CL::player_bullets + CL::bullets_respawn_amount)
    return ERROR;

  match.end();

  return NO_ERROR;
}

int static player_grabs_point_items() {
  std::string map_name(ITEMS_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  while (match.move_player(1, DOWN) && match.grab_item(1) == 0);
  while (match.move_player(1, LEFT) && match.grab_item(1) == 0);

  if (match.get_players().at(1).get_points()
      != CL::crown_points + CL::cup_points)
    return ERROR;

  match.end();

  return NO_ERROR;
}

int static rocket_spawns_where_it_should() {
  std::string map_name(ROCKET_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  unsigned int rocket_id = match.shoot_rocket(1);

  if (match.move_player(1, UP)) {
    return ERROR;
  }

  match.end();

  return NO_ERROR;
}

int static rocket_moves_once_correctly() {
  std::string map_name(ROCKET_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  unsigned int rocket_id = match.shoot_rocket(1);

  if (!match.move_rocket(rocket_id)) {
    return ERROR;
  }

  if (match.move_player(1, UP) && !match.move_player(1, UP)) {
    return ERROR;
  }

  match.end();

  return NO_ERROR;
}

int static rocket_moves_until_it_finds_a_player() {
  std::string map_name(ROCKET_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  unsigned int rocket_id = match.shoot_rocket(1);

  while (match.move_rocket(rocket_id));

  if (match.move_player(2, DOWN)) {
    return ERROR;
  }

  match.end();

  return NO_ERROR;
}

int static rocket_explodes_and_damages_player() {
  std::string map_name(ROCKET_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  unsigned int rocket_id = match.shoot_rocket(1);

  while (match.move_rocket(rocket_id));

  std::unordered_map<unsigned int, unsigned char>
      damages = match.explode_rocket(rocket_id, 1);

  if (match.get_players().at(2).get_health() == CL::player_health) {
    return ERROR;
  }

  if (damages.find(2) == damages.end()) {
    return ERROR;
  }

  if (damages.size() != 1) {
    return ERROR;
  }

  match.end();

  return NO_ERROR;
}

int static rocket_explodes_and_damages_multiple_players() {
  std::string map_name(ROCKET_MAP);
  Match match(1, 1, map_name);

  match.add_player(1);
  match.add_player(2);
  match.add_player(3);

  BlockingQueue<Packet> queue_mock;
  match.start(1, queue_mock);

  while (match.move_player(1, UP) && match.grab_item(1) == 0);

  unsigned int rocket_id = match.shoot_rocket(1);

  while (match.move_rocket(rocket_id));

  std::unordered_map<unsigned int, unsigned char>
      damages = match.explode_rocket(rocket_id, 1);

  if (match.get_players().at(2).get_health() == CL::player_health) {
    return ERROR;
  }

  if (match.get_players().at(3).get_health() == CL::player_health) {
    return ERROR;
  }

  if (match.get_players().at(3).get_health()
      < match.get_players().at(2).get_health()) {
    return ERROR;
  }

  if (damages.find(2) == damages.end()) {
    return ERROR;
  }

  if (damages.find(3) == damages.end()) {
    return ERROR;
  }

  if (damages.size() != 2) {
    return ERROR;
  }

  match.end();

  return NO_ERROR;
}
