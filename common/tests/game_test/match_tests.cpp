#include "match_tests.h"
#include "../tests_setup.h"
#include "../../../server/src/main/game/match.h"
#include "../../../server/src/main/game/sprites/items/medic_kit.h"
#include "../../../server/src/main/game/sprites/items/blood.h"
#include <cmath>
#include "client_mock.h"

int static can_move_up_player();
int static can_move_up_player_two_times();
int static can_move_up_until_wall();
int static grabs_medic_kit_and_restores_all_health();
int static grabs_medic_kit_and_restores_health_correctly();
int static walks_two_times_and_grabs_medic_kit();
int static grabs_blood_only_when_health_is_less_than_eleven();

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

  end_tests();
}

int static can_move_up_player() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_origin(),
                   angled_player_position.get_angle());

  // CLIENT MOCK
  Point next_position = next_position_up(angled_player_position);
  PointData point = {.x = next_position.getX(), .y = next_position.getY()};
  Event event = {.type = 1, .player_id = 1, .data = {.point = point}};

  match.enqueue_event(event);
  match.start();
  Event result = match.dequeue_result();

  if (result.type == 1 && result.player_id == 1
      && result.data.point.x == 100
      && result.data.point.y == 101)
    return NO_ERROR;

  return ERROR;
}

int static can_move_up_player_two_times() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_origin(),
                   angled_player_position.get_angle());

  // CLIENT MOCK
  Point position_1 = next_position_up(angled_player_position);
  PointData point_1 = {.x = position_1.getX(), .y = position_1.getY()};
  Event event_1 = {.type = 1, .player_id = 1, .data = {.point = point_1}};

  match.enqueue_event(event_1);

  Point position_2 = next_position_up(Ray(position_1, M_PI / 2));
  PointData point_2 = {.x = position_2.getX(), .y = position_2.getY()};
  Event event_2 = {.type = 1, .player_id = 1, .data = {.point = point_2}};

  match.enqueue_event(event_2);
  match.start();
  Event result = match.dequeue_result();

  if (result.type != 1 || result.player_id != 1
      || result.data.point.x != 100
      || result.data.point.y != 101)
    return ERROR;

  result = match.dequeue_result();

  if (result.type != 1 || result.player_id != 1
      || result.data.point.x != 100
      || result.data.point.y != 102)
    return ERROR;

  return NO_ERROR;
}

int static can_move_up_until_wall() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_origin(),
                   angled_player_position.get_angle());

  Point position = angled_player_position.get_origin();
  PointData point = {.x = position.getX(), .y = position.getY()};
  Event event = {.type = 1, .player_id = 1, .data = {.point = point}};

  for (int i = 0; i < 471; i++) {
    position = next_position_up(Ray(position, M_PI / 2));
    point = {.x = position.getX(), .y = position.getY()};
    event = {.type = 1, .player_id = 1, .data = {.point = point}};

    match.enqueue_event(event);
  }

  for (int i = 0; i < 100; i++)
    match.enqueue_event(event);

  match.start();

  Event result;

  for (int i = 101; i < 571; i++) {
    result = match.dequeue_result();
    if (result.data.point.y != i)
      return ERROR;
  }

  for (int i = 0; i < 100; i++) {
    result = match.dequeue_result();
    if (result.data.point.y != 570)
      return ERROR;
  }

  return NO_ERROR;
}

int static grabs_medic_kit_and_restores_all_health() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_origin(),
                   angled_player_position.get_angle());

  // CLIENT MOCK
  Point next_position = next_position_up(angled_player_position);
  PointData point = {.x = next_position.getX(), .y = next_position.getY()};
  Event event = {.type = 1, .player_id = 1, .data = {.point = point}};

  MedicKit *kit = new MedicKit(Point(100, 101));
  match.add_item(kit);

  match.enqueue_event(event);
  match.start();

  Event result = match.dequeue_result();

  if (result.type != 2 || result.player_id != 1
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

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_origin(),
                   angled_player_position.get_angle());

  // CLIENT MOCK
  Point next_position = next_position_up(angled_player_position);
  PointData point = {.x = next_position.getX(), .y = next_position.getY()};
  Event event = {.type = 1, .player_id = 1, .data = {.point = point}};

  MedicKit *kit = new MedicKit(Point(100, 101));
  match.add_item(kit);

  match.get_player(1).decrease_health(30);

  match.enqueue_event(event);
  match.start();

  Event result = match.dequeue_result();

  if (result.type != 2 || result.player_id != 1
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

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_origin(),
                   angled_player_position.get_angle());

  // CLIENT MOCK
  Point position_1 = next_position_up(angled_player_position);
  PointData point_1 = {.x = position_1.getX(), .y = position_1.getY()};
  Event event_1 = {.type = 1, .player_id = 1, .data = {.point = point_1}};

  match.enqueue_event(event_1);

  Point position_2 = next_position_up(Ray(position_1, M_PI / 2));
  PointData point_2 = {.x = position_2.getX(), .y = position_2.getY()};
  Event event_2 = {.type = 1, .player_id = 1, .data = {.point = point_2}};

  match.enqueue_event(event_2);

  MedicKit *kit = new MedicKit(Point(100, 102));
  match.add_item(kit);

  match.get_player(1).decrease_health(30);

  match.start();

  match.dequeue_result();
  Event result = match.dequeue_result();

  if (result.type != 2 || result.player_id != 1
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

  Match match(map);
  Ray angled_player_position = Ray(Point(100, 100), M_PI / 2);
  match.add_player(angled_player_position.get_origin(),
                   angled_player_position.get_angle());

  // CLIENT MOCK
  Point position = angled_player_position.get_origin();
  PointData point = {.x = position.getX(), .y = position.getY()};
  Event event = {.type = 1, .player_id = 1, .data = {.point = point}};

  for (int i = 0; i < 3; i++) {
    position = next_position_up(Ray(position, M_PI / 2));
    point = {.x = position.getX(), .y = position.getY()};
    event = {.type = 1, .player_id = 1, .data = {.point = point}};

    match.enqueue_event(event);
  }

  Blood *kit = new Blood(Point(100, 102));
  match.add_item(kit);

  match.start();

  position = next_position_down(Ray(position, M_PI / 2));
  point = {.x = position.getX(), .y = position.getY()};
  event = {.type = 1, .player_id = 1, .data = {.point = point}};

  match.enqueue_event(event);

  match.get_player(1).decrease_health(30);

  match.start();

  match.dequeue_result();
  Event result = match.dequeue_result();

  if (result.type != 1 || result.player_id != 1
      || result.data.point.x != 100 || result.data.point.y != 102) {
    return ERROR;
  }

  match.dequeue_result();
  result = match.dequeue_result();

  if (result.type != 2 || result.player_id != 1
      || result.data.item != 1) {
    return ERROR;
  }

  if (match.get_player(result.player_id).get_health()
      != 11) // TODO Use config loader
    return ERROR;

  return NO_ERROR;
}
