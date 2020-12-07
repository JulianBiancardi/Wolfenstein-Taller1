#include "../../main/server/game/player.h"
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
