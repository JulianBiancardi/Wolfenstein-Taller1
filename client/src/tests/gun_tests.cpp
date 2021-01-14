/*
#include "gun_tests.h"

#include <iostream>

#include "../../../server/src/main/game/collision_checker.h"
#include "../../../server/src/main/game/guns/chain_cannon.h"
#include "../../../server/src/main/game/guns/knife.h"
#include "../../../server/src/main/game/guns/pistol.h"
#include "../../../server/src/main/game/guns/rocket_launcher.h"
#include "../../../server/src/main/map.h"
 */

#include <unordered_map>

#include "../../common/src/main/config_loader.h"
#include "../main/guns/chain_cannon.h"
#include "../main/guns/knife.h"
#include "../main/guns/pistol.h"
#include "../main/guns/rocket_launcher.h"
#include "gun_tests.h"
/*
#include "../../../server/src/main/game/collision_checker.h"
#include "../../../server/src/main/game/player.h"
*/

#include <iostream>

#define WALL 1  // todo shouldn't be here

int static gun_creation_test();
int static chain_cannon_check_damaged();
int static machine_gun_check_damaged();
int static pistol_check_damaged();
int static rocket_launcher_check_damaged();
int static chain_cannon_shoot_get_player_bullets_amount();
int static chain_cannon_shoot_player2_get_shot();

// TODO Wrong place?
void fill_data(Matrix<int> &map_data) {
  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      if ((j == map_data.get_rows() - 1) || (j == 0) ||
          (i == map_data.get_columns() - 1) || (i == 0))
        map_data(j, i) = WALL;
    }
  }
}
void gun_tests() {
  begin_tests("GUNS");

  print_test("Las armas se crean correctamente", gun_creation_test, NO_ERROR);

  print_test("El arma Chain Cannon devuelve un valor entre 1 y 10",
             chain_cannon_check_damaged, NO_ERROR);

  print_test("El arma Machine Gun devuelve un valor entre 1 y 10",
             machine_gun_check_damaged, NO_ERROR);

  print_test("El arma Pistol devuelve un valor entre 1 y 10",
             pistol_check_damaged, NO_ERROR);

  print_test("El arma Rocket Launcher devuelve un valor entre 1 y 10",
             rocket_launcher_check_damaged, NO_ERROR);

  print_test(
      "El jugador dispara con el arma Chain Cannon y restan balas "
      "correctas",
      chain_cannon_shoot_get_player_bullets_amount, NO_ERROR);

  print_test(
      "El jugador1 dispara con Chain Cannon y jugador2 recibe el impacto",
      chain_cannon_shoot_player2_get_shot, NO_ERROR);
  end_tests();
}

int static gun_creation_test() {
  Knife knife;
  MachineGun machineGun;
  Pistol pistol;
  RocketLauncher rocketLauncher;
  return NO_ERROR;
}

int static chain_cannon_check_damaged() {
  ChainCannon chain_cannon;
  Matrix<int> map_data(640, 640, 0);
  fill_data(map_data);
  Map game_map(map_data);

  Player player1(0, 0, 0, chain_cannon);
  Player player2(5, 0, 0, chain_cannon);

  player1.shoot(game_map);
  int value = player2.get_health();

  if (value >= CL::player_health - 10 && value < CL::player_health)
    return NO_ERROR;
  return ERROR;
}

int static machine_gun_check_damaged() {
  MachineGun machine_gun;
  Matrix<int> map_data(640, 640, 0);
  fill_data(map_data);
  Map game_map(map_data);
  Player player1(0, 0, 0, machine_gun);
  Player player2(5, 0, 0, machine_gun);
  // player1.shoot_player(player2, machine_gun);
  int value = player2.get_health();
  if (value >= CL::player_health - 10 && value < CL::player_health)
    return NO_ERROR;
  return ERROR;
}

int static pistol_check_damaged() {
  Pistol pistol;
  Matrix<int> map_data(640, 640, 0);
  fill_data(map_data);
  Map game_map(map_data);
  Player player1(0, 0, 0 /*, 1*/, pistol);
  Player player2(5, 0, 0 /*, 2*/, pistol);
  // player1.shoot_player(player2, pistol);
  int value = player2.get_health();
  if (value >= CL::player_health - 10 && value < CL::player_health)
    return NO_ERROR;
  return ERROR;
}
int static rocket_launcher_check_damaged() {
  RocketLauncher rocket_launcher;
  Matrix<int> map_data(640, 640, 0);
  fill_data(map_data);
  Map game_map(map_data);
  Player player1(0, 0, 0 /*, 1*/, rocket_launcher);
  Player player2(5, 0, 0 /*, 2*/, rocket_launcher);
  // player1.shoot_player(player2, rocket_launcher);
  int value = player2.get_health();
  if (value >= CL::player_health - 10 && value < CL::player_health)
    return NO_ERROR;
  return ERROR;
}

int static chain_cannon_shoot_get_player_bullets_amount() {
  ChainCannon chain_cannon;
  Matrix<int> map_data(640, 640, 0);
  fill_data(map_data);
  Map game_map(map_data);
  Player player1(0, 0, 0 /*, 1*/, chain_cannon);
  Player player2(5, 0, 0 /*, 2*/, chain_cannon);
  // player1.shoot_player(player2, chain_cannon);
  if (player1.has_bullets(CL::player_bullets -
                          CL::chain_cannon_bullet_required))
    return NO_ERROR;
  return ERROR;
}
int static chain_cannon_shoot_player2_get_shot() {
  ChainCannon chain_cannon;
  Matrix<int> map_data(640, 640, 0);
  fill_data(map_data);
  Map game_map(map_data);
  Player player1(320, 639, 0 /*, 1*/, chain_cannon);
  Player player2(320, 50, 0 /*, 2*/, chain_cannon);

  std::unordered_map<int, Player> players;
  players.insert({1, player1});
  players.insert({2, player2});
  std::vector<Object *> objects;
  /*
    std::unordered_map<int, Item *> items;
    CollisionChecker checker(game_map, players, items, objects);
  */
  // player1.shoot_player(player2, chain_cannon);

  // player1.shoot(chain_cannon);//todo

  if (player2.get_health() < CL::player_health) return NO_ERROR;
  return ERROR;
}

/*
int static machine_gun_shoot_player2_get_shot() {
  MachineGun machine_gun;
  Matrix<int> map_data(640, 640, 0);
  fill_data(map_data);
  Map game_map(map_data);
  Player player1( 0, 0, 0, game_map);
  Player player2( 5, 0, 0, game_map);
  player1.shoot(player2, machine_gun);
  if (player1.has_bullets(CL::player_bullets-
      CL::machine_gun_bullet_required)) return NO_ERROR;
  return ERROR;
}
*/
