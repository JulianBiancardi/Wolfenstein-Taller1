#include "../../../server/src/main/game/player.h"
#include "../../../server/src/main/game/objects/table.h"
#include "../../../server/src/main/map.h"
#include "../tests_setup.h"
#include "client_mock.h"
#include <utility>

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

void move_up(Player& who, CollisionChecker& checker) {
  Point next_position =
      next_position_up(who.get_position(), Angle(who.get_angle()));
  if (checker.can_move(next_position, who))
    who.set_position(next_position);
}

void move_down(Player& who, CollisionChecker& checker) {
  Point next_position =
      next_position_down(who.get_position(), Angle(who.get_angle()));
  if (checker.can_move(next_position, who))
    who.set_position(next_position);
}

void move_right(Player& who, CollisionChecker& checker) {
  Point next_position =
      next_position_right(who.get_position(), Angle(who.get_angle()));
  if (checker.can_move(next_position, who))
    who.set_position(next_position);
}

void move_left(Player& who, CollisionChecker& checker) {
  Point next_position =
      next_position_left(who.get_position(), Angle(who.get_angle()));
  if (checker.can_move(next_position, who))
    who.set_position(next_position);
}

void move_up_right(Player& who, CollisionChecker& checker) {
  Point next_position =
      next_position_up_right(who.get_position(), Angle(who.get_angle()));
  if (checker.can_move(next_position, who))
    who.set_position(next_position);
}

void move_up_left(Player& who, CollisionChecker& checker) {
  Point next_position =
      next_position_up_left(who.get_position(), Angle(who.get_angle()));
  if (checker.can_move(next_position, who))
    who.set_position(next_position);
}

void move_down_right(Player& who, CollisionChecker& checker) {
  Point next_position =
      next_position_down_right(who.get_position(), Angle(who.get_angle()));
  if (checker.can_move(next_position, who))
    who.set_position(next_position);
}

void move_down_left(Player& who, CollisionChecker& checker) {
  Point next_position =
      next_position_down_left(who.get_position(), Angle(who.get_angle()));
  if (checker.can_move(next_position, who))
    who.set_position(next_position);
}

// FIXME Only works for current map settings
void player_tests() {
  begin_tests("PLAYER");

  print_test("El jugador se mueve correctamente", can_move_up, NO_ERROR);
  print_test("El jugador colisiona con una pared correctamente",
             collides_wall,
             NO_ERROR);
  print_test("El jugador camina hasta una pared y colisiona",
             walks_and_collides_wall,
             NO_ERROR);
  print_test("El jugador camina hacia atras mirando hacia adelante",
             walk_with_different_angle_and_direction,
             NO_ERROR);
  print_test("El jugador completa un path correctamente",
             complete_path_correctly,
             NO_ERROR);
  print_test("El jugador camina en diagonal",
             walk_diagonally,
             NO_ERROR);
  print_test("El jugador completa un path complicado correctamente",
             complete_difficult_path_correctly,
             NO_ERROR);
  print_test("El jugador colisiona correctamente",
             check_collisions,
             NO_ERROR);
  print_test("El jugador colisiona contra otro jugador",
             player_collides_against_other_player,
             NO_ERROR);
  print_test("Otro jugador colisiona contra otro jugador",
             another_player_collides_against_other_player,
             NO_ERROR);
  print_test("Jugador colisiona mesa",
             player_collides_against_table_from_side,
             NO_ERROR);
  print_test("Jugador colisiona mesa desde otro lado",
             player_collides_against_table_from_another_side,
             NO_ERROR);
  print_test("Colision simple",
             simplest_collision,
             NO_ERROR);
  print_test("Colision mas simple",
             second_simplest_collision,
             NO_ERROR);
  print_test("Colision diagonal con mesa",
             diagonal_collision_with_table,
             NO_ERROR);
  end_tests();
}

int static can_move_up() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 2, 1);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  move_up(players.at(1), checker);

  if (players.at(1).get_position().getX() == 100
      && players.at(1).get_position().getY() == 101)
    return NO_ERROR;

  return ERROR;
}

int static collides_wall() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(64, 64, 3 * M_PI / 2, 1);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  move_up(players.at(1), checker);

  if (players.at(1).get_position().getX() == 64
      && players.at(1).get_position().getY() == 64)
    return NO_ERROR;

  return ERROR;
}

int static walks_and_collides_wall() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(64, 64, 0, 1);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  int previous_x;
  do {
    previous_x = players.at(1).get_position().getX();
    move_up(players.at(1), checker);
  } while (previous_x != players.at(1).get_position().getX());

  if (players.at(1).get_position().getX() == 570
      && players.at(1).get_position().getY() == 64)
    return NO_ERROR;

  return ERROR;
}

int static walk_with_different_angle_and_direction() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(64, 64, 3 * M_PI / 2, 1);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  move_down(players.at(1), checker);

  if (players.at(1).get_position().getX() == 64
      && players.at(1).get_position().getY() == 65)
    return NO_ERROR;

  return ERROR;
}

int static complete_path_correctly() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, 0, 1);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  for (int i = 0; i < 100; i++) {
    move_up(players.at(1), checker);
  }
  for (int i = 0; i < 100; i++) {
    move_left(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() == 200
      && players.at(1).get_position().getY() == 200)
    return NO_ERROR;

  return ERROR;
}

int static walk_diagonally() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, 0, 1);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  move_up_left(players.at(1), checker);

  if (players.at(1).get_position().getX() > 100.5
      && players.at(1).get_position().getX() < 101
      && players.at(1).get_position().getY() > 100.5
      && players.at(1).get_position().getY() < 101)
    return NO_ERROR;

  return ERROR;
}

int static complete_difficult_path_correctly() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, 0, 1);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  for (int i = 0; i < 700; i++) {
    move_up(players.at(1), checker);
  }
  for (int i = 0; i < 100; i++) {
    move_left(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() == 570
      && players.at(1).get_position().getY() == 200)
    return NO_ERROR;

  return ERROR;
}

int static check_collisions() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 2, 1);
  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  for (int i = 0; i < 700; i++) {
    move_right(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() != 570
      || players.at(1).get_position().getY() != 100)
    return ERROR;

  for (int i = 0; i < 700; i++) {
    move_up(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() != 570
      || players.at(1).get_position().getY() != 570)
    return ERROR;

  for (int i = 0; i < 700; i++) {
    move_left(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() != 69
      || players.at(1).get_position().getY() != 570)
    return ERROR;

  for (int i = 0; i < 700; i++) {
    move_down(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() != 69
      || players.at(1).get_position().getY() != 69)
    return ERROR;

  return NO_ERROR;
}

int static player_collides_against_other_player() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player1(100, 100, M_PI / 2, 1);
  Player player2(100, 200, 0, 2);

  std::unordered_map<int, Player> players;
  players.insert({1, player1});
  players.insert({2, player2});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  for (int i = 0; i < 200; i++) {
    move_up(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() == 100
      && players.at(1).get_position().getY() == 190)
    return NO_ERROR;

  return ERROR;
}

int static another_player_collides_against_other_player() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player1(100, 100, M_PI, 1);
  Player player2(200, 200, 3 * M_PI / 2, 2);

  std::unordered_map<int, Player> players;
  players.insert({1, player1});
  players.insert({2, player2});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  for (int i = 0; i < 100; i++) {
    move_right(players.at(1), checker);
  }

  for (int i = 0; i < 100; i++) {
    move_right(players.at(2), checker);
  }

  if (players.at(2).get_position().getX() == 110
      && players.at(2).get_position().getY() == 200)
    return NO_ERROR;

  return ERROR;
}

int static player_collides_against_table_from_side() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 2, 1);

  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new Table(5, 4, Point(100, 120)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  for (int i = 0; i < 100; i++) {
    move_up(players.at(1), checker);
  }

  delete sprites[0];

  if (players.at(1).get_position().getX() == 100
      && players.at(1).get_position().getY() == 113)
    return NO_ERROR;

  return ERROR;
}

int static player_collides_against_table_from_another_side() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 2, 1);

  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new Table(10, 10, Point(200, 100)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  for (int i = 0; i < 200; i++) {
    move_right(players.at(1), checker);
  }

  delete sprites[0];

  if (players.at(1).get_position().getX() == 190
      && players.at(1).get_position().getY() == 100)
    return NO_ERROR;

  return ERROR;
}

int static simplest_collision() {
  Matrix<int> map_data(10, 10, 0); // Emulates map loaded
  map_data(0, 9) = WALL; //TODO Decide what to use
  map_data(9, 0) = WALL;
  Map map(map_data);
  Player player(0.5, 0.5, 0, 1);

  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  for (int i = 0; i < 100; i++) {
    move_up(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() == 3.5
      && players.at(1).get_position().getY() == 0.5)
    return NO_ERROR;

  return ERROR;
}

int static second_simplest_collision() {
  Matrix<int> map_data(10, 10, 0); // Emulates map loaded
  map_data(0, 9) = WALL; //TODO Decide what to use
  map_data(9, 0) = WALL;
  Map map(map_data);
  Player player(1, 1, 0, 1);

  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  for (int i = 0; i < 3; i++) {
    move_up(players.at(1), checker);
  }

  if (players.at(1).get_position().getX() == 4
      && players.at(1).get_position().getY() == 1)
    return NO_ERROR;

  return ERROR;
}

int static diagonal_collision_with_table() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 4, 1);

  std::unordered_map<int, Player> players;
  players.insert({1, player});
  std::vector<Object*> sprites;
  sprites.push_back(new Table(10, 10, Point(300, 300)));
  std::unordered_map<int, Item*> items;
  CollisionChecker checker(map, players, items, sprites);

  for (int i = 0; i < 300; i++) {
    move_up(players.at(1), checker);
  }

  delete sprites[0];

  if (players.at(1).get_position().getX() > 290.91
      && players.at(1).get_position().getY() < 290.92
      && players.at(1).get_position().getX() > 290.91
      && players.at(1).get_position().getY() < 290.92)
    return NO_ERROR;

  return ERROR;
}
