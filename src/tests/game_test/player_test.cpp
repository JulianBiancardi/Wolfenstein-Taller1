#include "../../main/server/game/player.h"
#include "../../main/server/game/objects/barrel.h"
#include "../../main/server/game/objects/table.h"
#include "../../main/map.h"
#include "../../main/matrix.h"
#include "../tests_setup.h"
#include <iostream>
#include <cmath>

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

void put_data(Matrix<int> &map_data) {
  for (int j = 0; j < 64; j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      map_data(i, j) = WALL;  // TOP
      map_data(j, i) = WALL;  // LEFT
      map_data(i, map_data.get_rows() - 1 - j) = WALL;  // BOT
      map_data(map_data.get_columns() - 1 - j, i) = WALL;  // RIGHT
    }
  }
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
  Player player(100, 100, M_PI / 2, map);
  player.move_up();
  if (player.get_position().getX() == 100
      && player.get_position().getY() == 101)
    return NO_ERROR;

  return ERROR;
}

int static collides_wall() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(64, 64, 3 * M_PI / 2, map);
  player.move_up();
  if (player.get_position().getX() == 64 && player.get_position().getY() == 64)
    return NO_ERROR;

  return ERROR;
}

int static walks_and_collides_wall() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(64, 64, 0, map);
  int previous_x, previous_y;
  do {
    previous_x = player.get_position().getX();
    previous_y = player.get_position().getY();
    player.move_up();
  } while (previous_x != player.get_position().getX());

  if (player.get_position().getX() == 570 && player.get_position().getY() == 64)
    return NO_ERROR;

  return ERROR;
}

int static walk_with_different_angle_and_direction() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(64, 64, 3 * M_PI / 2, map);
  player.move_down();

  if (player.get_position().getX() == 64 && player.get_position().getY() == 65)
    return NO_ERROR;

  return ERROR;
}

int static complete_path_correctly() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, 0, map);
  for (int i = 0; i < 100; i++) {
    player.move_up();
  }
  for (int i = 0; i < 100; i++) {
    player.move_left();
  }

  if (player.get_position().getX() == 200
      && player.get_position().getY() == 200)
    return NO_ERROR;

  return ERROR;
}

int static walk_diagonally() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, 0, map);
  player.move_up_left();

  if (player.get_position().getX() > 100.5
      && player.get_position().getX() < 101
      && player.get_position().getY() > 100.5
      && player.get_position().getY() < 101)
    return NO_ERROR;

  return ERROR;
}

int static complete_difficult_path_correctly() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, 0, map);
  for (int i = 0; i < 700; i++) {
    player.move_up();
  }
  for (int i = 0; i < 100; i++) {
    player.move_left();
  }

  if (player.get_position().getX() == 570
      && player.get_position().getY() == 200)
    return NO_ERROR;

  return ERROR;
}

int static check_collisions() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 2, map);

  for (int i = 0; i < 700; i++) {
    player.move_right();
  }

  if (player.get_position().getX() != 570
      || player.get_position().getY() != 100)
    return ERROR;

  for (int i = 0; i < 700; i++) {
    player.move_up();
  }

  if (player.get_position().getX() != 570
      || player.get_position().getY() != 570)
    return ERROR;

  for (int i = 0; i < 700; i++) {
    player.move_left();
  }

  if (player.get_position().getX() != 69
      || player.get_position().getY() != 570)
    return ERROR;

  for (int i = 0; i < 700; i++) {
    player.move_down();
  }

  if (player.get_position().getX() != 69
      || player.get_position().getY() != 69)
    return ERROR;

  return NO_ERROR;
}

int static player_collides_against_other_player() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player1(100, 100, M_PI / 2, map);
  Player player2(100, 200, 0, map);

  map.add_player(player1);
  map.add_player(player2);

  for (int i = 0; i < 200; i++) {
    player1.move_up();
  }

  if (player1.get_position().getX() == 100
      && player1.get_position().getY() == 190)
    return NO_ERROR;

  return ERROR;
}

int static another_player_collides_against_other_player() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player1(100, 100, M_PI, map);
  Player player2(200, 200, 3 * M_PI / 2, map);

  map.add_player(player1);
  map.add_player(player2);

  for (int i = 0; i < 100; i++) {
    player1.move_right();
  }

  for (int i = 0; i < 100; i++) {
    player2.move_right();
  }

  if (player2.get_position().getX() == 110
      && player2.get_position().getY() == 200)
    return NO_ERROR;

  return ERROR;
}

int static player_collides_against_table_from_side() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 2, map);
  Table table(5, 4, Point(100, 120));

  map.add_player(player);
  map.add_object(table);

  for (int i = 0; i < 100; i++) {
    player.move_up();
  }

  if (player.get_position().getX() == 100
      && player.get_position().getY() == 113)
    return NO_ERROR;

  return ERROR;
}

int static player_collides_against_table_from_another_side() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 2, map);
  Table table(10, 10, Point(200, 100));

  map.add_player(player);
  map.add_object(table);

  for (int i = 0; i < 200; i++) {
    player.move_right();
  }

  if (player.get_position().getX() == 190
      && player.get_position().getY() == 100)
    return NO_ERROR;

  return ERROR;
}

int static simplest_collision() {
  Matrix<int> map_data(10, 10, 0); // Emulates map loaded
  map_data(0, 9) = WALL; //TODO Decide what to use
  map_data(9, 0) = WALL;
  Map map(map_data);
  Player player(0.5, 0.5, 0, map);

  for (int i = 0; i < 100; i++) {
    player.move_up();
  }

  if (player.get_position().getX() == 3.5
      && player.get_position().getY() == 0.5)
    return NO_ERROR;

  return ERROR;
}

int static second_simplest_collision() {
  Matrix<int> map_data(10, 10, 0); // Emulates map loaded
  map_data(0, 9) = WALL; //TODO Decide what to use
  map_data(9, 0) = WALL;
  Map map(map_data);
  Player player(1, 1, 0, map);

  for (int i = 0; i < 3; i++) {
    player.move_up();
  }

  if (player.get_position().getX() == 4
      && player.get_position().getY() == 1)
    return NO_ERROR;

  return ERROR;
}

int static diagonal_collision_with_table() {
  Matrix<int> map_data(640, 640, 0); // Emulates map loaded
  put_data(map_data);
  Map map(map_data);
  Player player(100, 100, M_PI / 4, map);
  Table table(10, 10, Point(300, 300));

  map.add_player(player);
  map.add_object(table);

  for (int i = 0; i < 300; i++) {
    player.move_up();
  }

  if (player.get_position().getX() > 290.9
      && player.get_position().getY() < 292
      && player.get_position().getX() > 290.9
      && player.get_position().getY() < 292)
    return NO_ERROR;

  return ERROR;
}
