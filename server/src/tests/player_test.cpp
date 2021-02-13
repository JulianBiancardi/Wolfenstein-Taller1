#include "player_test.h"

#include "../main/game/player.h"
#include "../../../common/src/main/ids/gun_ids.h"
#include "../main/game/objects/door/door.h"
#include "client_mock.h"
#include "tests_setup.h"

#define TEST_MAP_SIZE 10

#define TEST_MAP_MOVEMENT "test_map_movement"
#define TEST_MAP_EMPTY "test_map_empty"
#define TEST_MAP_WITH_TABLE "test_map_with_table"
#define TEST_MAP_WITH_DOOR "test_map_with_door"
#define TEST_MAP_WITH_LOCKED_DOOR "test_map_with_locked_door"

int static can_move_up();
int static collides_wall();
int static walks_and_collides_wall();
int static walk_with_different_angle_and_direction();
int static complete_path_correctly();
int static walk_diagonally();
int static complete_difficult_path_correctly();
int static check_collisions();
int static player_collides_against_other_player();
int static another_player_collides_against_other_player();
int static player_collides_against_table_from_side();
int static player_collides_against_table_from_another_side();
int static diagonal_collision_with_table();
int static player_kills_are_correct();
int static player_respawns_correctly();
int static player_collides_against_door();
int static player_walks_through_door();
int static player_tries_to_pass_door_opens_it_and_does_it();
int static player_tries_to_open_locked_door_with_no_key();
int static player_opens_door_with_key();
int static player_opens_door_with_key_then_closes_it_and_other_opens_it();
int static player_cannot_close_door_if_it_is_under_it();

void move_up(Player& who, CollisionChecker& checker) {
  Point next_position = who.next_position(UP);
  if (checker.can_move(next_position, who)) who.set_position(next_position);
}

void move_down(Player& who, CollisionChecker& checker) {
  Point next_position = who.next_position(DOWN);
  if (checker.can_move(next_position, who)) who.set_position(next_position);
}

void move_right(Player& who, CollisionChecker& checker) {
  Point next_position = who.next_position(RIGHT);
  if (checker.can_move(next_position, who)) who.set_position(next_position);
}

void move_left(Player& who, CollisionChecker& checker) {
  Point next_position = who.next_position(LEFT);
  if (checker.can_move(next_position, who)) who.set_position(next_position);
}

void move_up_right(Player& who, CollisionChecker& checker) {
  Point next_position = who.next_position(UP_RIGHT);
  if (checker.can_move(next_position, who)) who.set_position(next_position);
}

void move_player_to(Player& who, CollisionChecker& checker, Point where) {
  if (checker.can_move(where, who)) who.set_position(where);
}

void player_tests() {
  begin_tests("PLAYER");

  if (CL::player_speed < EPSILON) {
    std::cout << "Configurar correctamente el epsilon de comparacion\n";
    end_tests();
  }

  print_test("El jugador se mueve correctamente", can_move_up, NO_ERROR);
  print_test("El jugador colisiona con una pared correctamente", collides_wall,
             NO_ERROR);
  print_test("El jugador camina hasta una pared y colisiona",
             walks_and_collides_wall, NO_ERROR);
  print_test("El jugador camina hacia atras mirando hacia adelante",
             walk_with_different_angle_and_direction, NO_ERROR);
  print_test("El jugador completa un path correctamente",
             complete_path_correctly, NO_ERROR);
  print_test("El jugador camina en diagonal", walk_diagonally, NO_ERROR);
  print_test("El jugador completa un path complicado correctamente",
             complete_difficult_path_correctly, NO_ERROR);
  print_test("El jugador colisiona correctamente", check_collisions, NO_ERROR);
  print_test("El jugador colisiona contra otro jugador",
             player_collides_against_other_player, NO_ERROR);
  print_test("Otro jugador colisiona contra otro jugador",
             another_player_collides_against_other_player, NO_ERROR);
  print_test("Jugador colisiona mesa", player_collides_against_table_from_side,
             NO_ERROR);
  print_test("Jugador colisiona mesa desde otro lado",
             player_collides_against_table_from_another_side, NO_ERROR);
  print_test("Colision diagonal con mesa", diagonal_collision_with_table,
             NO_ERROR);
  print_test("La cantidad de kills de un jugador es correcta",
             player_kills_are_correct, NO_ERROR);
  print_test("El jugador respawnea correctamente", player_respawns_correctly,
             NO_ERROR);
  print_test("El jugador colisiona contra una puerta cerrada",
             player_collides_against_door, NO_ERROR);
  print_test("El jugador abre puerta y pasa", player_walks_through_door,
             NO_ERROR);
  print_test("El jugador pasa la puerta solo al abrirla",
             player_tries_to_pass_door_opens_it_and_does_it, NO_ERROR);
  print_test("Jugador sin llave no puede abrir puerta",
             player_tries_to_open_locked_door_with_no_key, NO_ERROR);
  print_test("Jugador abre la puerta con llave", player_opens_door_with_key,
             NO_ERROR);
  print_test("Jugador abre la puerta, la cierra y otro la abre",
             player_opens_door_with_key_then_closes_it_and_other_opens_it,
             NO_ERROR);
  print_test("La puerta no se cierra si hay un jugador debajo",
             player_cannot_close_door_if_it_is_under_it, NO_ERROR);

  end_tests();
}

int static can_move_up() {
  std::string map_name(TEST_MAP_MOVEMENT);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);

  Point initial_position = map.get_player(1).get_position();

  move_up(map.get_player(1), checker);

  if (map.get_player(1).get_position().getX()
      == initial_position.getX() + CL::player_speed &&
      map.get_player(1).get_position().getY() == initial_position.getY())
    return NO_ERROR;

  return ERROR;
}

int static collides_wall() {
  std::string map_name(TEST_MAP_MOVEMENT);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);

  Point initial_position(TEST_MAP_SIZE - 1 - CL::player_mask_radio, 5);

  move_player_to(map.get_player(1), checker, initial_position);

  move_up(map.get_player(1), checker);

  if (map.get_player(1).get_position() == initial_position)
    return NO_ERROR;

  return ERROR;
}

int static walks_and_collides_wall() {
  std::string map_name(TEST_MAP_MOVEMENT);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);

  double initial_y = map.get_player(1).get_position().getY();

  double previous_x;
  do {
    previous_x = map.get_player(1).get_position().getX();
    move_up(map.get_player(1), checker);
  } while (previous_x != map.get_player(1).get_position().getX());

  if (double_compare(map.get_player(1).get_position().getX(),
                     TEST_MAP_SIZE - 1 - CL::player_mask_radio) &&
      map.get_player(1).get_position().getY() == initial_y)
    return NO_ERROR;

  return ERROR;
}

int static walk_with_different_angle_and_direction() {
  std::string map_name(TEST_MAP_MOVEMENT);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);

  Point initial_position = map.get_player(1).get_position();

  move_down(map.get_player(1), checker);

  if (map.get_player(1).get_position().getX()
      == initial_position.getX() - CL::player_speed &&
      map.get_player(1).get_position().getY() == initial_position.getY())
    return NO_ERROR;

  return ERROR;
}

int static complete_path_correctly() {
  std::string map_name(TEST_MAP_EMPTY);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2, 2));

  for (int i = 0; i < 40; i++) {
    move_up(map.get_player(1), checker);
  }

  for (int i = 0; i < 40; i++) {
    move_right(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(),
                     2 + 40 * CL::player_speed) &&
      double_compare(map.get_player(1).get_position().getY(),
                     2 + 40 * CL::player_speed))
    return NO_ERROR;

  return ERROR;
}

int static walk_diagonally() {
  std::string map_name(TEST_MAP_EMPTY);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2, 2));

  move_up_right(map.get_player(1), checker);

  if (double_compare(map.get_player(1).get_position().getX(),
                     map.get_player(1).get_position().getX()
                         + CL::player_speed * cos(7 * M_PI / 4))
      && double_compare(map.get_player(1).get_position().getY(),
                        map.get_player(1).get_position().getY()
                            - CL::player_speed * sin(7 * M_PI / 4)))
    return NO_ERROR;

  return ERROR;
}

int static complete_difficult_path_correctly() {
  std::string map_name(TEST_MAP_EMPTY);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2, 2));

  for (int i = 0; i < 100; i++) {
    move_up(map.get_player(1), checker);
  }

  for (int i = 0; i < 10; i++) {
    move_right(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(),
                     TEST_MAP_SIZE - 1 - CL::player_mask_radio) &&
      double_compare(map.get_player(1).get_position().getY(),
                     2 + 10 * CL::player_speed))
    return NO_ERROR;

  return ERROR;
}

int static check_collisions() {
  std::string map_name(TEST_MAP_EMPTY);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2, 2));

  for (int i = 0; i < 140; i++) {
    move_up(map.get_player(1), checker);
  }

  if (!double_compare(map.get_player(1).get_position().getX(),
                      TEST_MAP_SIZE - 1 - CL::player_mask_radio) ||
      !double_compare(map.get_player(1).get_position().getY(),
                      2))
    return ERROR;

  for (int i = 0; i < 140; i++) {
    move_right(map.get_player(1), checker);
  }

  if (!double_compare(map.get_player(1).get_position().getX(),
                      TEST_MAP_SIZE - 1 - CL::player_mask_radio) ||
      !double_compare(map.get_player(1).get_position().getY(),
                      TEST_MAP_SIZE - 1 - CL::player_mask_radio))
    return ERROR;

  for (int i = 0; i < 200; i++) {
    move_down(map.get_player(1), checker);
  }

  if (!double_compare(map.get_player(1).get_position().getX(),
                      1 + CL::player_mask_radio) ||
      !double_compare(map.get_player(1).get_position().getY(),
                      TEST_MAP_SIZE - 1 - CL::player_mask_radio))
    return ERROR;

  for (int i = 0; i < 200; i++) {
    move_left(map.get_player(1), checker);
  }

  if (!double_compare(map.get_player(1).get_position().getX(),
                      1 + CL::player_mask_radio) ||
      !double_compare(map.get_player(1).get_position().getY(),
                      1 + CL::player_mask_radio))
    return ERROR;

  return NO_ERROR;
}

int static player_collides_against_other_player() {
  std::string map_name(TEST_MAP_EMPTY);
  Map map(map_name);
  map.add_player(1);
  map.add_player(2);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2, 2));
  move_player_to(map.get_player(2), checker, Point(2, 7));

  for (int i = 0; i < 100; i++) {
    move_right(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(), 2) &&
      double_compare(map.get_player(1).get_position().getY(),
                     map.get_player(2).get_position().getY()
                         - 2 * CL::player_mask_radio))
    return NO_ERROR;

  return ERROR;
}

int static another_player_collides_against_other_player() {
  std::string map_name(TEST_MAP_EMPTY);
  Map map(map_name);
  map.add_player(1);
  map.add_player(2);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2, 2));
  move_player_to(map.get_player(2), checker, Point(7, 7));

  for (int i = 0; i < 50; i++) {
    move_right(map.get_player(1), checker);
  }

  for (int i = 0; i < 100; i++) {
    move_down(map.get_player(2), checker);
  }

  if (double_compare(map.get_player(2).get_position().getX(),
                     map.get_player(1).get_position().getX()
                         + 2 * CL::player_mask_radio) &&
      double_compare(map.get_player(2).get_position().getY(), 7))
    return NO_ERROR;

  return ERROR;
}

int static player_collides_against_table_from_side() {
  std::string map_name(TEST_MAP_WITH_TABLE);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2.5, 5.5));

  for (int i = 0; i < 30; i++) {
    move_up(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(),
                     5.5 - CL::table_width / 2 - CL::player_mask_radio
                         - CL::player_speed)
      && map.get_player(1).get_position().getY() == 5.5)
    return NO_ERROR;

  return ERROR;
}

int static player_collides_against_table_from_another_side() {
  std::string map_name(TEST_MAP_WITH_TABLE);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(5.5, 2.5));

  for (int i = 0; i < 100; i++) {
    move_right(map.get_player(1), checker);
  }

  if (map.get_player(1).get_position().getX() == 5.5 &&
      double_compare(map.get_player(1).get_position().getY(),
                     5.5 - CL::table_depth / 2 - CL::player_mask_radio
                         - CL::player_speed))
    return NO_ERROR;

  return ERROR;
}

int static diagonal_collision_with_table() {
  std::string map_name(TEST_MAP_WITH_TABLE);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);

  for (int i = 0; i < 60; i++) {
    move_up_right(map.get_player(1), checker);
  }

  if (fabs(map.get_player(1).get_position().distance_from(Point(5, 5)))
      < CL::player_mask_radio)
    return ERROR;

  Point previous_point(map.get_player(1).get_position().getX() -
                           CL::player_speed * cos(7 * M_PI / 4),
                       map.get_player(1).get_position().getY() +
                           CL::player_speed * sin(7 * M_PI / 4));

  if (fabs(previous_point.distance_from(Point(5, 5))) > CL::player_mask_radio)
    return NO_ERROR;

  return ERROR;
}

int static player_kills_are_correct() {
  Player player(5, 5, 0, 1);

  player.add_kill();

  if (player.get_kills() == 1) return NO_ERROR;

  return ERROR;
}

int static player_respawns_correctly() {
  Player player(5, 5, 0, 1);

  player.add_gun(MACHINE_GUN_ID);
  player.add_gun(ROCKET_LAUNCHER_ID);

  player.receive_damage(CL::player_health / 2);

  player.respawn();

  if (player.get_bullets() != CL::player_respawn_bullets) return ERROR;

  if (player.get_lives() != CL::player_lives - 1) return ERROR;

  if (player.get_active_gun() != PISTOL_ID) return ERROR;

  if (player.get_health() != CL::player_health) return ERROR;

  if (player.has_gun(PISTOL_ID) && player.has_gun(KNIFE_ID) &&
      !player.has_gun(ROCKET_LAUNCHER_ID) && !player.has_gun(MACHINE_GUN_ID))
    return NO_ERROR;

  return ERROR;
}

int static player_collides_against_door() {
  std::string map_name(TEST_MAP_WITH_DOOR);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2.5, 5.5));

  for (int i = 0; i < 60; i++) {
    move_up(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(),
                     5.5 - 0.5 - CL::player_mask_radio - CL::player_speed)
      && map.get_player(1).get_position().getY() == 5.5)
    return NO_ERROR;

  return ERROR;
}

int static player_walks_through_door() {
  std::string map_name(TEST_MAP_WITH_DOOR);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2, 5));

  ((Door*) map.get_object(1))->interact(map.get_player(1), checker);

  for (int i = 0; i < 60; i++) {
    move_up(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(), 8)
      && map.get_player(1).get_position().getY() == 5)
    return NO_ERROR;

  return ERROR;
}

int static player_tries_to_pass_door_opens_it_and_does_it() {
  std::string map_name(TEST_MAP_WITH_DOOR);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2, 5));

  for (int i = 0; i < 60; i++) {
    move_up(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(),
                     5 - 0.5 - CL::player_mask_radio - CL::player_speed)
      && map.get_player(1).get_position().getY() == 5)
    return NO_ERROR;

  Point previous(map.get_player(1).get_position());

  ((Door*) map.get_object(1))->interact(map.get_player(1), checker);

  for (int i = 0; i < 20; i++) {
    move_up(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(),
                     previous.getX() + 2)
      && map.get_player(1).get_position().getY() == 5)
    return NO_ERROR;

  return ERROR;
}

int static player_tries_to_open_locked_door_with_no_key() {
  std::string map_name(TEST_MAP_WITH_LOCKED_DOOR);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2.5, 5.5));

  ((Door*) map.get_object(1))->interact(map.get_player(1), checker);

  for (int i = 0; i < 60; i++) {
    move_up(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(),
                     5.5 - 0.5 - CL::player_mask_radio - CL::player_speed)
      && map.get_player(1).get_position().getY() == 5.5)
    return NO_ERROR;

  return ERROR;
}

int static player_opens_door_with_key() {
  std::string map_name(TEST_MAP_WITH_LOCKED_DOOR);
  Map map(map_name);
  map.add_player(1);
  map.get_player(1).add_key();

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2, 5));

  ((Door*) map.get_object(1))->interact(map.get_player(1), checker);

  for (int i = 0; i < 60; i++) {
    move_up(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(), 8)
      && map.get_player(1).get_position().getY() == 5)
    return NO_ERROR;

  return ERROR;
}

int static player_opens_door_with_key_then_closes_it_and_other_opens_it() {
  std::string map_name(TEST_MAP_WITH_LOCKED_DOOR);
  Map map(map_name);
  map.add_player(1);
  map.add_player(2);
  map.get_player(1).add_key();

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2, 5));

  ((Door*) map.get_object(1))->interact(map.get_player(1), checker);
  ((Door*) map.get_object(1))->interact(map.get_player(1), checker);
  ((Door*) map.get_object(1))->interact(map.get_player(2), checker);

  for (int i = 0; i < 60; i++) {
    move_up(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(), 8)
      && map.get_player(1).get_position().getY() == 5)
    return NO_ERROR;

  return ERROR;
}

int static player_cannot_close_door_if_it_is_under_it() {
  std::string map_name(TEST_MAP_WITH_DOOR);
  Map map(map_name);
  map.add_player(1);

  CollisionChecker checker(map);
  move_player_to(map.get_player(1), checker, Point(2.5, 5.5));

  ((Door*) map.get_object(1))->interact(map.get_player(1), checker);

  move_player_to(map.get_player(1), checker, Point(5.5, 5.5));

  ((Door*) map.get_object(1))->interact(map.get_player(1), checker);

  if (!(((Door*) map.get_object(1))->is_open())) {
    return ERROR;
  }

  Point previous(map.get_player(1).get_position());

  for (int i = 0; i < 2 / CL::player_speed; i++) {
    move_up(map.get_player(1), checker);
  }

  ((Door*) map.get_object(1))->interact(map.get_player(1), checker);

  if ((((Door*) map.get_object(1))->is_open())) {
    return ERROR;
  }

  if (double_compare(map.get_player(1).get_position().getX(),
                     previous.getX() + 2)
      && map.get_player(1).get_position().getY() == 5.5)
    return NO_ERROR;

  return ERROR;
}
