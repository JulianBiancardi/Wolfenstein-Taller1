#include "../main/game/player.h"

#include "../../../common/src/main/ids/gun_ids.h"
#include "../../../common/src/main/ids/movement_ids.h"
#include "../main/game/objects/door/lock_door.h"
#include "../main/game/objects/door/normal_door.h"
#include "../main/game/objects/table.h"
#include "../main/map.h"
#include "client_mock.h"
#include "tests_setup.h"

#define TEST_MAP_SIZE 10
#define EPSILON 0.1

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
int static simplest_collision();
int static second_simplest_collision();
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

void move_up_left(Player& who, CollisionChecker& checker) {
  Point next_position = who.next_position(UP_LEFT);
  if (checker.can_move(next_position, who)) who.set_position(next_position);
}

void move_down_right(Player& who, CollisionChecker& checker) {
  Point next_position = who.next_position(DOWN_RIGHT);
  if (checker.can_move(next_position, who)) who.set_position(next_position);
}

void move_down_left(Player& who, CollisionChecker& checker) {
  Point next_position = who.next_position(DOWN_LEFT);
  if (checker.can_move(next_position, who)) who.set_position(next_position);
}

Matrix<int> create_base_map() {
  Matrix<int> map_data(TEST_MAP_SIZE, TEST_MAP_SIZE, 0);
  for (size_t i = 0; i < TEST_MAP_SIZE; i++) {
    map_data(i, 0) = WALL;
    map_data(i, TEST_MAP_SIZE - 1) = WALL;
    map_data(0, i) = WALL;
    map_data(TEST_MAP_SIZE - 1, i) = WALL;
  }
  return map_data;
}

bool double_compare(double x, double y) {
  return fabs(x - y) < EPSILON;
}

void player_tests() {
  begin_tests("PLAYER");

  if (CL::player_pace < EPSILON) {
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
  /*print_test("El jugador completa un path complicado correctamente",
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
  print_test("Colision simple", simplest_collision, NO_ERROR);
  print_test("Colision mas simple", second_simplest_collision, NO_ERROR);
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
  */

  end_tests();
}

int static can_move_up() {
  Matrix<int> map_data = create_base_map();
  Map map(map_data);
  map.add_spawn_point(5, 5);
  map.add_player(1);

  CollisionChecker checker(map);

  move_up(map.get_player(1), checker);

  if (map.get_player(1).get_position().getX() == 5 + CL::player_pace &&
      map.get_player(1).get_position().getY() == 5)
    return NO_ERROR;

  return ERROR;
}

int static collides_wall() {
  Matrix<int> map_data = create_base_map();
  Map map(map_data);
  map.add_spawn_point(8.45, 5);
  map.add_player(1);

  CollisionChecker checker(map);

  move_up(map.get_player(1), checker);

  if (map.get_player(1).get_position().getX() == 8.45 &&
      map.get_player(1).get_position().getY() == 5)
    return NO_ERROR;

  return ERROR;
}

int static walks_and_collides_wall() {
  Matrix<int> map_data = create_base_map();
  Map map(map_data);
  map.add_spawn_point(5, 5);
  map.add_player(1);

  CollisionChecker checker(map);

  double previous_x;
  do {
    previous_x = map.get_player(1).get_position().getX();
    move_up(map.get_player(1), checker);
  } while (previous_x != map.get_player(1).get_position().getX());

  if (double_compare(map.get_player(1).get_position().getX(),
                     TEST_MAP_SIZE - 1 - CL::player_mask_radio) &&
      map.get_player(1).get_position().getY() == 5)
    return NO_ERROR;

  return ERROR;
}

int static walk_with_different_angle_and_direction() {
  Matrix<int> map_data = create_base_map();
  Map map(map_data);
  map.add_spawn_point(5, 5);
  map.add_player(1);

  CollisionChecker checker(map);

  move_down(map.get_player(1), checker);

  if (map.get_player(1).get_position().getX() == 5 - CL::player_pace &&
      map.get_player(1).get_position().getY() == 5)
    return NO_ERROR;

  return ERROR;
}

int static complete_path_correctly() {
  Matrix<int> map_data = create_base_map();
  Map map(map_data);
  map.add_spawn_point(2, 2);
  map.add_player(1);

  CollisionChecker checker(map);

  for (int i = 0; i < 40; i++) {
    move_up(map.get_player(1), checker);
  }

  for (int i = 0; i < 40; i++) {
    move_right(map.get_player(1), checker);
  }

  if (double_compare(map.get_player(1).get_position().getX(),
                     2 + 40 * CL::player_pace) &&
      double_compare(map.get_player(1).get_position().getY(),
                     2 + 40 * CL::player_pace))
    return NO_ERROR;

  return ERROR;
}

int static walk_diagonally() {
  Matrix<int> map_data = create_base_map();
  Map map(map_data);
  map.add_spawn_point(2, 2);
  map.add_player(1);

  CollisionChecker checker(map);

  move_up_right(map.get_player(1), checker);

  if (double_compare(map.get_player(1).get_position().getX(),
                     map.get_player(1).get_position().getX()
                         + CL::player_pace * cos(7 * M_PI / 4))
      && double_compare(map.get_player(1).get_position().getY(),
                        map.get_player(1).get_position().getY()
                            - CL::player_pace * sin(7 * M_PI / 4)))
    return NO_ERROR;

  return ERROR;
}
/*
int static complete_difficult_path_correctly() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME add manually to map
  Player player(100, 100, 0);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  for (int i = 0; i < 700; i++) {
    move_up(players.at(1), checker);
  }

  for (int i = 0; i < 100; i++) {
    move_right(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() == 570 &&
      players.at(1).get_position().getY() == 200)
    return NO_ERROR;

  return ERROR;
}

int static check_collisions() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME add manually to map
  Player player(100, 100, M_PI / 2);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  for (int i = 0; i < 700; i++) {
    move_right(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() != 570 ||
      players.at(1).get_position().getY() != 100)
    return ERROR;

  for (int i = 0; i < 700; i++) {
    move_down(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() != 570 ||
      players.at(1).get_position().getY() != 570)
    return ERROR;

  for (int i = 0; i < 700; i++) {
    move_left(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() != 69 ||
      players.at(1).get_position().getY() != 570)
    return ERROR;

  for (int i = 0; i < 700; i++) {
    move_up(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() != 69 ||
      players.at(1).get_position().getY() != 69)
    return ERROR;

  return NO_ERROR;
}

int static player_collides_against_other_player() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME add manually to map
  Player player1(100, 100, M_PI / 2);
  Player player2(100, 200, 0);

  std::unordered_map<int, Player> players;
  players.insert({1, player1});
  players.insert({2, player2});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  for (int i = 0; i < 200; i++) {
    move_down(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() == 100 &&
      players.at(1).get_position().getY() == 189)
    return NO_ERROR;

  return ERROR;
}

int static another_player_collides_against_other_player() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME add manually to map
  Player player1(100, 100, M_PI);
  Player player2(200, 200, 3 * M_PI / 2);

  std::unordered_map<int, Player> players;
  players.insert({1, player1});
  players.insert({2, player2});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  for (int i = 0; i < 100; i++) {
    move_left(players.at(1), checker);
  }

  for (int i = 0; i < 100; i++) {
    move_right(players.at(2), checker);
  }

  if (players.at(2).get_position().getX() == 111 &&
      players.at(2).get_position().getY() == 200)
    return NO_ERROR;

  return ERROR;
}

int static player_collides_against_table_from_side() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 2);

  // FIXME add manually to map
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new Table(5, 4, Point(100, 120)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  for (int i = 0; i < 100; i++) {
    move_down(players.at(1), checker);
  }

  delete sprites[0];

  if (players.at(1).get_position().getX() == 100 &&
      players.at(1).get_position().getY() == 112)
    return NO_ERROR;

  return ERROR;
}

int static player_collides_against_table_from_another_side() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 2);

  // FIXME add manually to map
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new Table(10, 10, Point(200, 100)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  for (int i = 0; i < 200; i++) {
    move_right(players.at(1), checker);
  }

  delete sprites[0];

  if (players.at(1).get_position().getX() == 189 &&
      players.at(1).get_position().getY() == 100)
    return NO_ERROR;

  return ERROR;
}

int static simplest_collision() {
  Matrix<int> map_data(10, 10, 0);  // Emulates map loaded
  map_data(9, 0) = WALL;
  Map map(map_data);
  Player player(0.5, 0.5, 0);

  // FIXME Add manually to map
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  for (int i = 0; i < 100; i++) {
    move_up(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() == 3.5 &&
      players.at(1).get_position().getY() == 0.5)
    return NO_ERROR;

  return ERROR;
}

int static second_simplest_collision() {
  Matrix<int> map_data(10, 10, 0);  // Emulates map loaded
  map_data(9, 0) = WALL;
  Map map(map_data);
  Player player(1, 1, 0);

  // FIXME Add manually to map
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  for (int i = 0; i < 3; i++) {
    move_up(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() == 4 &&
      players.at(1).get_position().getY() == 1)
    return NO_ERROR;

  return ERROR;
}

int static diagonal_collision_with_table() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, 7 * M_PI / 4);

  // FIXME Add manually to map
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new Table(10, 10, Point(300, 300)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  for (int i = 0; i < 300; i++) {
    move_up(players.at(1), checker);
  }

  delete sprites[0];

  if (players.at(1).get_position().getX() > 290.91 &&
      players.at(1).get_position().getY() < 290.92 &&
      players.at(1).get_position().getX() > 290.91 &&
      players.at(1).get_position().getY() < 290.92)
    return NO_ERROR;

  return ERROR;
}

int static player_kills_are_correct() {
  Player player(5, 5, 0);

  player.add_kill();

  if (player.get_kills() == 1) return NO_ERROR;

  return ERROR;
}

int static player_respawns_correctly() {
  Player player(5, 5, 0);

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
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME Add manually to map
  Player player(100, 100, 3 * M_PI / 2);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new NormalDoor(Point(100, 101)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  move_up(players.at(1), checker);

  delete sprites[0];

  if (players.at(1).get_position().getX() == 100 &&
      players.at(1).get_position().getY() == 100)
    return NO_ERROR;

  return ERROR;
}

int static player_walks_through_door() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME add manually to map
  Player player(100, 100, 3 * M_PI / 2);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new NormalDoor(Point(100, 101)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  ((Door*)sprites.at(0))->interact(players.at(1), checker);

  move_up(players.at(1), checker);

  delete sprites[0];

  if (players.at(1).get_position().getX() == 100 &&
      players.at(1).get_position().getY() == 101)
    return NO_ERROR;

  return ERROR;
}

int static player_tries_to_pass_door_opens_it_and_does_it() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME add manually to map
  Player player(100, 100, 3 * M_PI / 2);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;

  sprites.push_back(new NormalDoor(Point(100, 101)));

  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  move_up(players.at(1), checker);

  if (players.at(1).get_position().getX() != 100 ||
      players.at(1).get_position().getY() != 100)
    return ERROR;

  ((Door*)sprites.at(0))->interact(players.at(1), checker);

  move_up(players.at(1), checker);

  if (players.at(1).get_position().getX() != 100 ||
      players.at(1).get_position().getY() != 101)
    return ERROR;

  delete sprites[0];

  return NO_ERROR;
}

int static player_tries_to_open_locked_door_with_no_key() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME add manually to map
  Player player(100, 100, 3 * M_PI / 2);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new LockedDoor(Point(100, 101)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  ((Door*)sprites.at(0))->interact(players.at(1), checker);
  move_up(players.at(1), checker);

  delete sprites[0];

  if (players.at(1).get_position().getX() == 100 &&
      players.at(1).get_position().getY() == 100)
    return NO_ERROR;

  return ERROR;
}

int static player_opens_door_with_key() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME add manually to map
  Player player(100, 100, 3 * M_PI / 2);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new LockedDoor(Point(100, 101)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  players.at(1).add_key();
  ((Door*)sprites.at(0))->interact(players.at(1), checker);

  move_up(players.at(1), checker);

  delete sprites[0];

  if (players.at(1).has_keys()) return ERROR;

  if (players.at(1).get_position().getX() == 100 &&
      players.at(1).get_position().getY() == 101)
    return NO_ERROR;

  return ERROR;
}

int static player_opens_door_with_key_then_closes_it_and_other_opens_it() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME add manually to map
  Player player_1(100, 95, 3 * M_PI / 2);
  Player player_2(200, 200, M_PI / 2);
  std::unordered_map<int, Player> players;
  players.insert({1, player_1});
  players.insert({2, player_2});
  std::vector<Object*> sprites;
  sprites.push_back(new LockedDoor(Point(100, 101)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  players.at(1).add_key();
  ((Door*)sprites.at(0))->interact(players.at(1), checker);
  ((Door*)sprites.at(0))->interact(players.at(1), checker);
  ((Door*)sprites.at(0))->interact(players.at(2), checker);

  for (int i = 0; i < 6; i++) move_up(players.at(1), checker);

  delete sprites[0];

  if (players.at(1).get_position().getX() == 100 &&
      players.at(1).get_position().getY() == 101)
    return NO_ERROR;

  return ERROR;
}

int static player_cannot_close_door_if_it_is_under_it() {
  Matrix<int> map_data(640, 640, 0);  // Emulates map loaded
  put_data(map_data);
  Map map(map_data);

  // FIXME add manually to map
  Player player(100, 90, 3 * M_PI / 2);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new NormalDoor(Point(100, 100)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map);

  ((Door*)sprites.at(0))->interact(players.at(1), checker);

  if (!(((Door*)sprites.at(0))->is_open())) return ERROR;

  for (int i = 0; i < 10; i++) move_up(players.at(1), checker);

  ((Door*)sprites.at(0))->interact(players.at(1), checker);

  if (!(((Door*)sprites.at(0))->is_open())) return ERROR;

  delete sprites[0];

  if (players.at(1).get_position().getX() == 100 &&
      players.at(1).get_position().getY() == 100)
    return NO_ERROR;

  return ERROR;
}
*/