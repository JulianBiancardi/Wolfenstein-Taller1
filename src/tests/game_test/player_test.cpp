#include "../../main/server/game/player.h"
#include "../../main/server/game/map.h"
#include "../tests_setup.h"
#include <iostream>

int static can_move_up();
int static collides_wall();
int static walks_and_collides_wall();

// FIXME Only works for current map settings
int main(){
  begin_tests("PLAYER");

  print_test("El jugador se mueve correctamente", can_move_up, NO_ERROR);
  print_test("El jugador colisiona con una pared correctamente", collides_wall, NO_ERROR);
  print_test("El jugador camina hasta una pared y colisiona", walks_and_collides_wall, NO_ERROR);

  end_tests();
  return 0;
}

int static can_move_up() {
  Player player(100,100,0);
  player.move_up();
  if(player.get_position().getX() == 100 && player.get_position().getY() == 99)
  	return NO_ERROR;

  return ERROR;
}

int static collides_wall() {
  Player player(64,64,0);
  player.move_up();
  if(player.get_position().getX() == 64 && player.get_position().getY() == 64)
  	return NO_ERROR;

  return ERROR;
}

int static walks_and_collides_wall() {
  Player player(64,64,0);
  int previous_x, previous_y;
  do {
  	previous_x = player.get_position().getX();
  	previous_y = player.get_position().getY();
  	player.move_right();
  } while (previous_x != player.get_position().getX());

  if(player.get_position().getX() == 575 && player.get_position().getY() == 64)
  	return NO_ERROR;

  return ERROR;
}
