#include "../../main/server/game/player.h"
#include "../../main/map.h"
#include "../../main/matrix.h"
#include "../tests_setup.h"
#include <iostream>
#include <cmath>

int static can_move_up();
int static collides_wall();
int static walks_and_collides_wall();

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
int main() {
  begin_tests("PLAYER");

  print_test("El jugador se mueve correctamente", can_move_up, NO_ERROR);
  print_test("El jugador colisiona con una pared correctamente",
             collides_wall,
             NO_ERROR);
  print_test("El jugador camina hasta una pared y colisiona",
             walks_and_collides_wall,
             NO_ERROR);

  end_tests();
  return 0;
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

  if (player.get_position().getX() == 575 && player.get_position().getY() == 64)
    return NO_ERROR;

  return ERROR;
}
