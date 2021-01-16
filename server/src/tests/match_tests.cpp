#include "match_tests.h"
#include "../../../common/src/tests/tests_setup.h"
#include "../main/game/match.h"
#include "../main/game/objects/items/medic_kit.h"
#include "../main/game/objects/items/blood.h"
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
  end_tests();
}

int static can_move_up_player() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_angle());

  // CLIENT MOCK
  Point next_position = next_position_up(angled_player_position.get_origin(),
                                         Angle(angled_player_position.get_angle()));
  PointData point = {.x = next_position.getX(), .y = next_position.getY()};
  packet_t event = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point}};

  match.enqueue_event(event);
  match.start();
  packet_t result = match.dequeue_result(1);

  if (result.type == MOVE_PACKET && result.player_id == 1
      && result.data.point.x == 100
      && result.data.point.y == 101)
    return NO_ERROR;

  return ERROR;
}

int static can_move_up_player_two_times() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_angle());

  // CLIENT MOCK
  Point position_1 = next_position_up(angled_player_position.get_origin(),
                                      Angle(angled_player_position.get_angle()));
  PointData point_1 = {.x = position_1.getX(), .y = position_1.getY()};
  packet_t event_1 = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point_1}};

  match.enqueue_event(event_1);

  Point position_2 = next_position_up(position_1, Angle(M_PI / 2));
  PointData point_2 = {.x = position_2.getX(), .y = position_2.getY()};
  packet_t event_2 = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point_2}};

  match.enqueue_event(event_2);
  match.start();
  packet_t result = match.dequeue_result(1);

  if (result.type != MOVE_PACKET || result.player_id != 1
      || result.data.point.x != 100
      || result.data.point.y != 101)
    return ERROR;

  result = match.dequeue_result(1);

  if (result.type != MOVE_PACKET || result.player_id != 1
      || result.data.point.x != 100
      || result.data.point.y != 102)
    return ERROR;

  return NO_ERROR;
}

int static can_move_up_until_wall() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_angle());

  Point position = angled_player_position.get_origin();
  PointData point = {.x = position.getX(), .y = position.getY()};
  packet_t event = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point}};

  for (int i = 0; i < 471; i++) {
    position = next_position_up(position, Angle(M_PI / 2));
    point = {.x = position.getX(), .y = position.getY()};
    event = {.type = MOVE_PACKET, .player_id = 1, .data = {.point = point}};

    match.enqueue_event(event);
  }

  for (int i = 0; i < 100; i++)
    match.enqueue_event(event);

  match.start();

  packet_t result;

  for (int i = 101; i < 571; i++) {
    result = match.dequeue_result(1);
    if (result.data.point.y != i)
      return ERROR;
  }

  for (int i = 0; i < 100; i++) {
    result = match.dequeue_result(1);
    if (result.data.point.y != 570)
      return ERROR;
  }

  return NO_ERROR;
}

int static grabs_medic_kit_and_restores_all_health() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_medic_kit(Point(100, 101));

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_angle());

  // CLIENT MOCK
  Point next_position = next_position_up(angled_player_position.get_origin(),
                                         Angle(angled_player_position.get_angle()));
  PointData point = {.x = next_position.getX(), .y = next_position.getY()};
  packet_t event = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point}};

  match.enqueue_event(event);

  match.get_player(1).decrease_health(5);

  match.start();

  packet_t result = match.dequeue_result(1);

  if (result.type != GRAB_PACKET || result.player_id != 1
      || result.data.item != 1)
    return ERROR;

  if (match.get_player(result.player_id).get_health()
      != 40) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static grabs_medic_kit_and_restores_health_correctly() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_medic_kit(Point(100, 101));

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_angle());

  // CLIENT MOCK
  Point next_position = next_position_up(angled_player_position.get_origin(),
                                         Angle(angled_player_position.get_angle()));
  PointData point = {.x = next_position.getX(), .y = next_position.getY()};
  packet_t event = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point}};

  match.get_player(1).decrease_health(30);

  match.enqueue_event(event);
  match.start();

  packet_t result = match.dequeue_result(1);

  if (result.type != GRAB_PACKET || result.player_id != 1
      || result.data.item != 1) {
    return ERROR;
  }

  if (match.get_player(result.player_id).get_health()
      != 30) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static walks_two_times_and_grabs_medic_kit() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_medic_kit(Point(100, 102));

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_angle());

  // CLIENT MOCK
  Point position_1 = next_position_up(angled_player_position.get_origin(),
                                      Angle(angled_player_position.get_angle()));
  PointData point_1 = {.x = position_1.getX(), .y = position_1.getY()};
  packet_t event_1 = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point_1}};

  match.enqueue_event(event_1);

  Point position_2 = next_position_up(position_1, Angle(M_PI / 2));
  PointData point_2 = {.x = position_2.getX(), .y = position_2.getY()};
  packet_t event_2 = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point_2}};

  match.enqueue_event(event_2);

  match.get_player(1).decrease_health(30);

  match.start();

  match.dequeue_result(1);
  packet_t result = match.dequeue_result(1);

  if (result.type != GRAB_PACKET || result.player_id != 1
      || result.data.item != 1) {
    return ERROR;
  }

  if (match.get_player(result.player_id).get_health()
      != 30) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static grabs_blood_only_when_health_is_less_than_eleven() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_blood(Point(100, 102));

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_angle());

  // CLIENT MOCK
  Point position = angled_player_position.get_origin();
  PointData point = {.x = position.getX(), .y = position.getY()};
  packet_t event = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point}};

  for (int i = 0; i < 3; i++) {
    position = next_position_up(position, Angle(M_PI / 2));
    point = {.x = position.getX(), .y = position.getY()};
    event = {.type = MOVE_PACKET, .player_id = 1, .data = {.point = point}};

    match.enqueue_event(event);
  }

  match.start();

  position = next_position_down(position, Angle(M_PI / 2));
  point = {.x = position.getX(), .y = position.getY()};
  event = {.type = MOVE_PACKET, .player_id = 1, .data = {.point = point}};

  match.enqueue_event(event);

  match.get_player(1).decrease_health(30);

  match.start();

  match.dequeue_result(1);
  packet_t result = match.dequeue_result(1);

  if (result.type != MOVE_PACKET || result.player_id != 1
      || result.data.point.x != 100 || result.data.point.y != 102) {
    return ERROR;
  }

  match.dequeue_result(1);
  result = match.dequeue_result(1);

  if (result.type != GRAB_PACKET || result.player_id != 1
      || result.data.item != 1) {
    return ERROR;
  }

  if (match.get_player(result.player_id).get_health()
      != 11) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static medic_kit_disappears_after_grabbing_it() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_medic_kit(Point(100, 101));

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_angle());

  // CLIENT MOCK
  Point position = angled_player_position.get_origin();
  PointData point = {.x = position.getX(), .y = position.getY()};
  packet_t event = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point}};

  for (int i = 0; i < 2; i++) {
    position = next_position_up(position, Angle(M_PI / 2));
    point = {.x = position.getX(), .y = position.getY()};
    event = {.type = MOVE_PACKET,
        .player_id = 1,
        .data = {.point = point}};

    match.enqueue_event(event);
  }

  position = next_position_down(position, Angle(M_PI / 2));
  point = {.x = position.getX(), .y = position.getY()};
  event = {.type = MOVE_PACKET, .player_id = 1, .data = {.point = point}};

  match.enqueue_event(event);

  match.get_player(1).decrease_health(30);

  match.start();

  packet_t result = match.dequeue_result(1);

  if (result.type != GRAB_PACKET || result.player_id != 1
      || result.data.item != 1) {
    return ERROR;
  }

  for (int i = 0; i < 2; i++) {
    match.dequeue_result(1);
  }

  result = match.dequeue_result(1);

  if (result.type != MOVE_PACKET || result.player_id != 1
      || result.data.point.x != 100 || result.data.point.y != 101) {
    return ERROR;
  }

  if (match.get_player(result.player_id).get_health()
      != 30) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static one_player_moves_and_grabs_medic_kit_and_all_players_are_notified() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_spawn_point(Point(300, 300));

  map.add_medic_kit(Point(100, 101));

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_angle());
  match.add_player(M_PI / 2);

  // CLIENT MOCK
  Point next_position = next_position_up(angled_player_position.get_origin(),
                                         Angle(angled_player_position.get_angle()));
  PointData point = {.x = next_position.getX(), .y = next_position.getY()};
  packet_t event = {.type = MOVE_PACKET,
      .player_id = 1,
      .data = {.point = point}};

  match.enqueue_event(event);

  match.get_player(1).decrease_health(30);

  match.start();

  packet_t result_1 = match.dequeue_result(1);
  packet_t result_2 = match.dequeue_result(2);

  if (result_1.type != GRAB_PACKET || result_1.player_id != 1
      || result_1.data.item != 1) {
    return ERROR;
  }

  if (result_2.type != GRAB_PACKET || result_2.player_id != 1
      || result_2.data.item != 1) {
    return ERROR;
  }

  result_1 = match.dequeue_result(1);
  result_2 = match.dequeue_result(2);

  if (result_1.type != MOVE_PACKET || result_1.player_id != 1
      || result_1.data.point.x != 100 || result_1.data.point.y != 101) {
    return ERROR;
  }

  if (result_2.type != MOVE_PACKET || result_2.player_id != 1
      || result_2.data.point.x != 100 || result_2.data.point.y != 101) {
    return ERROR;
  }

  if (match.get_player(result_1.player_id).get_health()
      != 30) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}

int static player_shoots_enemy() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));
  map.add_spawn_point(Point(200, 200));

  Match match(map);
  match.add_player(M_PI / 2);
  match.add_player(M_PI / 3);

  // CLIENT MOCK
  ShootData shot = {.damage_done = 10, .enemy_shot = 2, .bullets_shot = 2};
  packet_t event = {.type = SHOT_HIT_PACKET,
      .player_id = 1,
      .data = {.shot = shot}};

  match.enqueue_event(event);

  match.start();

  packet_t result = match.dequeue_result(2);

  if (result.type != DAMAGE_PACKET || result.player_id != 2
      || result.data.damage != 10)
    return ERROR;

  if (match.get_player(1).get_bullets() != CL::player_bullets - 2)
    return ERROR;

  if (match.get_player(2).get_health() != CL::player_health - 10)
    return ERROR;

  return NO_ERROR;
}

int static player_shoots_nobody() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  Match match(map);
  match.add_player(M_PI / 2);

  // CLIENT MOCK
  packet_t event = {.type = SHOT_MISS_PACKET,
      .player_id = 1,
      .data = {.bullets_shot = 2}};

  match.enqueue_event(event);

  match.start();

  if (match.get_player(1).get_bullets() != CL::player_bullets - 2)
    return ERROR;

  return NO_ERROR;
}

int static player_shoots_enemy_over_blood_and_grabs_it() {
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
  ShootData shot = {.damage_done = 30, .enemy_shot = 2, .bullets_shot = 2};
  packet_t event = {.type = SHOT_HIT_PACKET,
      .player_id = 1,
      .data = {.shot = shot}};

  match.enqueue_event(event);

  match.start();

  packet_t result = match.dequeue_result(2);

  if (result.type != DAMAGE_PACKET || result.player_id != 2
      || result.data.damage != 30)
    return ERROR;

  result = match.dequeue_result(2);

  if (result.type != GRAB_PACKET || result.player_id != 2
      || result.data.item != 1)
    return ERROR;

  result = match.dequeue_result(1);

  if (result.type != GRAB_PACKET || result.player_id != 2
      || result.data.item != 1)
    return ERROR;

  if (match.get_player(1).get_bullets() != CL::player_bullets - 2)
    return ERROR;

  if (match.get_player(2).get_health()
      != CL::player_health - 30 + CL::blood_health_recovered)
    return ERROR;

  return NO_ERROR;
}

int static player_with_max_bullets_shoots_and_grabs_bullets() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  map.add_spawn_point(Point(100, 100));

  map.add_bullets(Point(100, 100));

  Match match(map);
  match.add_player(M_PI / 2);
  match.get_player(1).add_bullets(CL::player_max_bullets);

  // CLIENT MOCK
  packet_t event = {.type = SHOT_MISS_PACKET,
      .player_id = 1,
      .data = {.bullets_shot = 0}};

  match.enqueue_event(event);

  match.start();

  if (match.has_result_events_left(1))
    return ERROR;

  event = {.type = SHOT_MISS_PACKET,
      .player_id = 1,
      .data = {.bullets_shot = 5}};

  match.enqueue_event(event);

  match.start();

  packet_t result = match.dequeue_result(1);

  if (result.type != GRAB_PACKET || result.player_id != 1
      || result.data.item != 1)
    return ERROR;

  if (match.get_player(1).get_bullets()
      != CL::player_max_bullets - event.data.bullets_shot
          + 5) //TODO Use configloader
    return ERROR;

  return NO_ERROR;
}

int static player_changes_gun() {
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
  packet_t event = {.type = CHANGE_GUN_PACKET,
      .player_id = 1,
      .data = {.gun = 3}};

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
