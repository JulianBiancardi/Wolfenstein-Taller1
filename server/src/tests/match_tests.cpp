#include "match_tests.h"
#include "../../../common/src/tests/tests_setup.h"
#include "../main/game/match.h"
#include "../main/events/event_building.h"
#include <cmath>
#include "client_mock.h"

int static can_move_up_player();
int static can_move_up_player_two_times();
int static can_move_up_until_wall();
int static grabs_medic_kit_and_restores_all_health();
int static grabs_medic_kit_and_restores_health_correctly();
int static walks_two_times_and_grabs_medic_kit();
int static grabs_blood_only_when_health_is_less_than_eleven();
int static medic_kit_disappears_after_grabbing_it();
int static one_player_moves_and_grabs_medic_kit_and_all_players_are_notified();
int static player_shoots_enemy();
int static player_shoots_nobody();
int static player_shoots_enemy_over_blood_and_grabs_it();
int static player_with_max_bullets_shoots_and_grabs_bullets();
int static player_changes_gun();
int static players_spawn_where_it_should();
int static player_kills_enemy_and_it_respawns();
int static player_kills_enemy_and_it_is_no_longer_in_the_map();
int static player_grabs_gun_correctly();
int static player_cannot_grab_gun();
int static player_kills_enemy_and_grabs_drop();
int static player_grabs_point_items();

// TODO Use configloder for generic tests
void match_tests() {
  begin_tests("MATCH");

  print_test("Al mover un jugador, la respuesta generada es correcta",
             can_move_up_player,
             NO_ERROR);
  print_test("Muevo un jugador dos veces",
             can_move_up_player_two_times,
             NO_ERROR);
  print_test("Muevo un jugador hasta pared",
             can_move_up_until_wall,
             NO_ERROR);
  print_test("Jugador se mueve, agarra kit medico y recupera toda la salud",
             grabs_medic_kit_and_restores_all_health,
             NO_ERROR);
  print_test("Jugador se mueve, agarra kit medico y recupera salud",
             grabs_medic_kit_and_restores_health_correctly,
             NO_ERROR);
  print_test("Jugador se mueve dos veces y agarra kit medico",
             walks_two_times_and_grabs_medic_kit,
             NO_ERROR);
  print_test("Jugador agarra la sangre solo cuando tiene menos de 11 de vida",
             grabs_blood_only_when_health_is_less_than_eleven,
             NO_ERROR);
  print_test("El kit medico desaparece al agarrarse",
             medic_kit_disappears_after_grabbing_it,
             NO_ERROR);
  print_test(
      "Se notifican a todos los jugadores que uno se movio y agarro un kit medico",
      one_player_moves_and_grabs_medic_kit_and_all_players_are_notified,
      NO_ERROR);
  print_test("Jugador dispara correctamente a otro",
             player_shoots_enemy,
             NO_ERROR);
  print_test("Jugador dispara pero no acierta",
             player_shoots_nobody,
             NO_ERROR);
  print_test("Jugador recibe disparo y agarra sangre",
             player_shoots_enemy_over_blood_and_grabs_it,
             NO_ERROR);
  print_test("Jugador agarra balas solo luego de disparar",
             player_with_max_bullets_shoots_and_grabs_bullets,
             NO_ERROR);
  print_test("Jugador cambia de arma correctamente",
             player_changes_gun,
             NO_ERROR);
  print_test("Los jugadores spawnean donde deberian",
             players_spawn_where_it_should,
             NO_ERROR);
  print_test("Jugador mata enemigo y respawnea",
             player_kills_enemy_and_it_respawns,
             NO_ERROR);
  print_test("Enemigo muere definitivamente y desaparece",
             player_kills_enemy_and_it_is_no_longer_in_the_map,
             NO_ERROR);
  print_test("Jugador agarra arma",
             player_grabs_gun_correctly,
             NO_ERROR);
  print_test("Jugador no puede agarrar arma",
             player_cannot_grab_gun,
             NO_ERROR);
  print_test("Jugador agarra drop de muerte de otro",
             player_kills_enemy_and_grabs_drop,
             NO_ERROR);
  print_test("Jugador agarra items de puntos y se le suman",
             player_grabs_point_items,
             NO_ERROR);

  end_tests();
}

int static can_move_up_player() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  Match match(map);
  match.add_player(3 * M_PI / 2);

  // CLIENT MOCK
  packet_t event = build_move_packet(1, UP);

  match.enqueue_event(event);
  match.start();
  packet_t result = match.dequeue_result(1);

  if (result.type == MOVE_PACKET && result.player_id == 1
      && result.data.direction == UP)
    return NO_ERROR;

  return ERROR;
}

int static can_move_up_player_two_times() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  Match match(map);
  match.add_player(3 * M_PI / 2);

  // CLIENT MOCK
  packet_t event = build_move_packet(1, UP);

  match.enqueue_event(event);
  match.enqueue_event(event);

  match.start();
  packet_t result = match.dequeue_result(1);

  if (result.type != MOVE_PACKET || result.player_id != 1
      || result.data.direction != UP)
    return ERROR;

  result = match.dequeue_result(1);

  if (result.type != MOVE_PACKET || result.player_id != 1
      || result.data.direction != UP)
    return ERROR;

  return NO_ERROR;
}

int static can_move_up_until_wall() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), 3 * M_PI / 2);
  match.add_player(3 * M_PI / 2);

  packet_t event;
  for (int i = 0; i < 571; i++) {
    event = build_move_packet(1, UP);
    match.enqueue_event(event);
  }

  match.start();

  packet_t result;

  for (int i = 101; i < 571; i++) {
    result = match.dequeue_result(1);
    if (result.data.direction != UP)
      return ERROR;
  }

  for (int i = 0; i < 100; i++) {
    result = match.dequeue_result(1);
    if (result.data.direction != INVALID)
      return ERROR;
  }

  return NO_ERROR;
}

int static grabs_medic_kit_and_restores_all_health() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_medic_kit(Point(100, 101));

  Match match(map);
  match.add_player(3 * M_PI / 2);

  // CLIENT MOCK
  packet_t event = build_move_packet(2, UP);

  match.enqueue_event(event);

  match.get_player(2).receive_damage(5);

  match.start();

  packet_t result = match.dequeue_result(2);

  if (result.type != MOVE_PACKET || result.player_id != 2
      || result.data.direction != UP)
    return ERROR;

  result = match.dequeue_result(2);

  if (result.type != GRAB_PACKET || result.player_id != 2
      || result.data.item != 1)
    return ERROR;

  if (match.get_player(result.player_id).get_health()
      != 40) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static grabs_medic_kit_and_restores_health_correctly() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_medic_kit(Point(100, 101));

  Match match(map);
  match.add_player(3 * M_PI / 2);

  // CLIENT MOCK
  packet_t event = build_move_packet(2, UP);

  match.get_player(2).receive_damage(30);

  match.enqueue_event(event);
  match.start();

  match.dequeue_result(2);
  packet_t result = match.dequeue_result(2);

  if (result.type != GRAB_PACKET || result.player_id != 2
      || result.data.item != 1) {
    return ERROR;
  }

  if (match.get_player(result.player_id).get_health()
      != 30) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static walks_two_times_and_grabs_medic_kit() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_medic_kit(Point(100, 102));

  Match match(map);
  match.add_player(3 * M_PI / 2);

  // CLIENT MOCK
  packet_t event = build_move_packet(2, UP);

  match.enqueue_event(event);
  match.enqueue_event(event);

  match.get_player(2).receive_damage(30);

  match.start();

  match.dequeue_result(2);
  match.dequeue_result(2);
  packet_t result = match.dequeue_result(2);

  if (result.type != GRAB_PACKET || result.player_id != 2
      || result.data.item != 1) {
    return ERROR;
  }

  if (match.get_player(result.player_id).get_health()
      != 30) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static grabs_blood_only_when_health_is_less_than_eleven() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_blood(Point(100, 102));

  Match match(map);
  match.add_player(3 * M_PI / 2);

  // CLIENT MOCK
  packet_t event;
  for (int i = 0; i < 3; i++) {
    event = build_move_packet(2, UP);
    match.enqueue_event(event);
  }

  match.start();

  event = build_move_packet(2, DOWN);

  match.enqueue_event(event);

  match.get_player(2).receive_damage(30);

  match.start();

  match.dequeue_result(2);
  match.dequeue_result(2);
  packet_t result = match.dequeue_result(2);

  if (result.type != MOVE_PACKET || result.player_id != 2
      || result.data.direction != UP) {
    return ERROR;
  }

  match.dequeue_result(2);
  result = match.dequeue_result(2);

  if (result.type != GRAB_PACKET || result.player_id != 2
      || result.data.item != 1) {
    return ERROR;
  }

  if (match.get_player(result.player_id).get_health()
      != 11) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static medic_kit_disappears_after_grabbing_it() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_medic_kit(Point(100, 101));

  Match match(map);
  match.add_player(3 * M_PI / 2);

  // CLIENT MOCK
  packet_t event;
  for (int i = 0; i < 2; i++) {
    event = build_move_packet(2, UP);
    match.enqueue_event(event);
  }

  event = build_move_packet(2, DOWN);

  match.enqueue_event(event);

  match.get_player(2).receive_damage(30);

  match.start();

  match.dequeue_result(2);
  packet_t result = match.dequeue_result(2);

  if (result.type != GRAB_PACKET || result.player_id != 2
      || result.data.item != 1) {
    return ERROR;
  }

  match.dequeue_result(2);
  result = match.dequeue_result(2);

  if (result.type != MOVE_PACKET || result.player_id != 2
      || result.data.direction != DOWN) {
    return ERROR;
  }

  if (match.get_player(result.player_id).get_health()
      != 30) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static one_player_moves_and_grabs_medic_kit_and_all_players_are_notified() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_spawn_point(Point(300, 300));

  map.add_medic_kit(Point(100, 101));

  Match match(map);
  match.add_player(3 * M_PI / 2);
  match.add_player(M_PI / 2);

  // CLIENT MOCK
  packet_t event = build_move_packet(2, UP);

  match.enqueue_event(event);

  match.get_player(2).receive_damage(30);

  match.start();

  packet_t result_1 = match.dequeue_result(2);
  packet_t result_2 = match.dequeue_result(3);

  if (result_1.type != MOVE_PACKET || result_1.player_id != 2
      || result_1.data.direction != UP) {
    return ERROR;
  }

  if (result_2.type != MOVE_PACKET || result_2.player_id != 2
      || result_2.data.direction != UP) {
    return ERROR;
  }

  result_1 = match.dequeue_result(2);
  result_2 = match.dequeue_result(3);

  if (result_1.type != GRAB_PACKET || result_1.player_id != 2
      || result_1.data.item != 1) {
    return ERROR;
  }

  if (result_2.type != GRAB_PACKET || result_2.player_id != 2
      || result_2.data.item != 1) {
    return ERROR;
  }

  if (match.get_player(result_1.player_id).get_health()
      != 30) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static player_shoots_enemy() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_spawn_point(Point(200, 200));

  Match match(map);
  match.add_player(M_PI / 2);
  match.add_player(M_PI / 3);

  // CLIENT MOCK
  packet_t event = build_damage_packet(1, 10, 2);

  match.enqueue_event(event);

  match.start();

  packet_t result = match.dequeue_result(2);

  if (result.type != DAMAGE_PACKET || result.player_id != 1
      || result.data.shot.damage_done != 10 || result.data.shot.enemy_shot != 2)
    return ERROR;

  if (match.get_player(2).get_health() != CL::player_health - 10)
    return ERROR;

  return NO_ERROR;
}

int static player_shoots_nobody() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  Match match(map);
  match.add_player(M_PI / 2);

  // CLIENT MOCK
  packet_t event = build_damage_packet(1, 0, -1);

  match.enqueue_event(event);

  match.start();

  if (match.get_player(1).get_bullets()
      != CL::player_bullets - CL::pistol_bullet_required)
    return ERROR;

  return NO_ERROR;
}

int static player_shoots_enemy_over_blood_and_grabs_it() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_spawn_point(Point(200, 200));

  map.add_blood(Point(200, 200));

  Match match(map);
  match.add_player(M_PI / 2);
  match.add_player(M_PI / 3);

  // CLIENT MOCK
  packet_t event = build_damage_packet(2, 30, 3);

  match.enqueue_event(event);

  match.start();

  packet_t result = match.dequeue_result(3);

  if (result.type != DAMAGE_PACKET || result.player_id != 2
      || result.data.shot.damage_done != 30 || result.data.shot.enemy_shot != 3)
    return ERROR;

  result = match.dequeue_result(3);

  if (result.type != GRAB_PACKET || result.player_id != 3
      || result.data.item != 1)
    return ERROR;

  match.dequeue_result(2);
  result = match.dequeue_result(2);

  if (result.type != GRAB_PACKET || result.player_id != 3
      || result.data.item != 1)
    return ERROR;

  if (match.get_player(3).get_health()
      != CL::player_health - 30 + CL::blood_health_recovered)
    return ERROR;

  return NO_ERROR;
}

int static player_with_max_bullets_shoots_and_grabs_bullets() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_bullets(Point(100, 100));

  Match match(map);
  match.add_player(M_PI / 2);
  match.get_player(2).add_bullets(CL::player_max_bullets);
  match.get_player(2).change_gun(KNIFE_ID);

  // CLIENT MOCK
  packet_t event = build_damage_packet(2, 0, -1);

  match.enqueue_event(event);

  match.start();

  if (match.has_result_events_left(2))
    return ERROR;

  match.get_player(2).change_gun(PISTOL_ID);

  event = build_damage_packet(2, 0, -1);

  match.enqueue_event(event);

  match.start();

  packet_t result = match.dequeue_result(2);

  if (result.type != GRAB_PACKET || result.player_id != 2
      || result.data.item != 1)
    return ERROR;

  if (match.get_player(2).get_bullets()
      != CL::player_max_bullets - CL::pistol_bullet_required
          + CL::bullets_amount)
    return ERROR;

  return NO_ERROR;
}

int static player_changes_gun() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_spawn_point(Point(200, 200));

  Match match(map);
  match.add_player(M_PI / 2);
  match.add_player(M_PI / 3);

  match.get_player(1).add_gun(3);

  // CLIENT MOCK
  packet_t event = build_change_gun_packet(1, 3);

  match.enqueue_event(event);

  match.start();

  packet_t result = match.dequeue_result(2);

  if (result.type != CHANGE_GUN_PACKET || result.player_id != 1
      || result.data.gun != 3)
    return ERROR;

  if (match.has_result_events_left(1))
    return ERROR;

  if (match.get_player(1).get_active_gun() != 3)
    return ERROR;

  return NO_ERROR;
}

int static players_spawn_where_it_should() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_spawn_point(Point(200, 200));
  map.add_spawn_point(Point(300, 300));

  Match match(map);
  match.add_player(M_PI / 2);
  match.add_player(M_PI / 2);
  match.add_player(M_PI / 2);

  for (int i = 1; i <= 3; i++) {
    if (match.get_player(i).get_position().getX() != 100 * i
        || match.get_player(i).get_position().getY() != 100 * i)
      return ERROR;
  }

  if (match.get_player(1).get_position() == match.get_player(2).get_position())
    return ERROR;

  if (match.get_player(1).get_position() == match.get_player(3).get_position())
    return ERROR;

  if (match.get_player(2).get_position() == match.get_player(3).get_position())
    return ERROR;

  return NO_ERROR;
}

int static player_kills_enemy_and_it_respawns() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_spawn_point(Point(200, 200));

  Match match(map);
  match.add_player(M_PI / 2);
  match.add_player(M_PI / 3);

  // CLIENT MOCK
  packet_t event = build_damage_packet(1, CL::player_health + 10.0, 2);

  match.enqueue_event(event);

  match.start();

  packet_t result = match.dequeue_result(2);

  if (result.type != DAMAGE_PACKET || result.player_id != 1
      || result.data.shot.damage_done != CL::player_health + 10.0
      || result.data.shot.enemy_shot != 2)
    return ERROR;

  result = match.dequeue_result(1);

  if (result.type != DAMAGE_PACKET || result.player_id != 1
      || result.data.shot.damage_done != CL::player_health + 10.0
      || result.data.shot.enemy_shot != 2)
    return ERROR;

  if (match.get_player(2).get_position() != Point(200, 200))
    return ERROR;

  return NO_ERROR;
}

int static player_kills_enemy_and_it_is_no_longer_in_the_map() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_spawn_point(Point(100, 110));

  Match match(map);
  match.add_player(3 * M_PI / 2);
  match.get_player(1).add_bullets(CL::player_max_bullets);
  match.add_player(M_PI / 3);

  // CLIENT MOCK
  packet_t event;
  for (int i = 0; i < CL::player_lives; i++) {
    event = build_damage_packet(1, CL::player_health + 10.0, 2);
    match.enqueue_event(event);
  }

  for (int i = 0; i < 20; i++) {
    event = build_move_packet(1, UP);
    match.enqueue_event(event);
  }

  match.start();

  if (match.get_player(1).get_position() != Point(100, 120))
    return ERROR;

  return NO_ERROR;
}

int static player_grabs_gun_correctly() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_machine_gun(Point(100, 99));

  Match match(map);
  match.add_player(M_PI / 2);

  // CLIENT MOCK;
  packet_t event = build_move_packet(2, UP);

  match.enqueue_event(event);

  match.start();

  match.dequeue_result(2);
  packet_t result = match.dequeue_result(2);

  if (result.type != GRAB_PACKET || result.player_id != 2
      || result.data.item != 1)
    return ERROR;

  if (!match.get_player(2).has_gun(MACHINE_GUN_ID))
    return ERROR;

  return NO_ERROR;
}

int static player_cannot_grab_gun() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_machine_gun(Point(100, 99));

  Match match(map);
  match.add_player(M_PI / 2);
  match.get_player(2).add_gun(MACHINE_GUN_ID);

  // CLIENT MOCK;
  packet_t event = build_move_packet(2, UP);

  match.enqueue_event(event);

  match.start();

  packet_t result = match.dequeue_result(2);

  if (result.type != MOVE_PACKET || result.player_id != 2
      || result.data.direction != UP)
    return ERROR;

  if (match.has_result_events_left(2))
    return ERROR;

  if (!match.get_player(2).has_gun(MACHINE_GUN_ID))
    return ERROR;

  return NO_ERROR;
}

int static player_kills_enemy_and_grabs_drop() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_spawn_point(Point(200, 200));

  Match match(map);
  match.add_player(3 * M_PI / 2);
  match.add_player(M_PI / 3);

  match.get_player(2).set_position(Point(100, 110));
  match.get_player(2).add_key();
  match.get_player(2).add_gun(MACHINE_GUN_ID);
  match.get_player(2).change_gun(MACHINE_GUN_ID);

  // CLIENT MOCK
  packet_t event = build_damage_packet(1, CL::player_health + 10.0, 2);

  match.enqueue_event(event);

  for (int i = 0; i < 10; i++) {
    event = build_move_packet(1, UP);
    match.enqueue_event(event);
  }

  for (int i = 0; i < 5; i++) {
    event = build_move_packet(1, LEFT);
    match.enqueue_event(event);
  }

  for (int i = 0; i < 10; i++) {
    event = build_move_packet(1, RIGHT);
    match.enqueue_event(event);
  }

  match.start();

  int grab_events_found = 0;
  packet_t result;
  while (match.has_result_events_left(1)) {
    result = match.dequeue_result(1);
    if (result.type == GRAB_PACKET)
      grab_events_found++;
  }

  if (grab_events_found != 3)
    return ERROR;

  if (match.get_player(1).has_keys() && match.get_player(1).get_bullets()
      == CL::player_bullets - CL::pistol_bullet_required
          + CL::bullets_respawn_amount
      && match.get_player(1).has_gun(MACHINE_GUN_ID))
    return NO_ERROR;

  return ERROR;
}

int static player_grabs_point_items() {
  Identifiable::reset_id();

  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_cross(Point(100, 105));
  map.add_crown(Point(100, 110));

  Match match(map);
  match.add_player(3 * M_PI / 2);

  // CLIENT MOCK
  packet_t event;
  for (int i = 0; i < 20; i++) {
    event = build_move_packet(3, UP);
    match.enqueue_event(event);
  }

  match.start();

  if (match.get_player(3).get_points() != CL::crosses_points + CL::crown_points)
    return ERROR;

  return NO_ERROR;
}
