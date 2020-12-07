#include "gun_tests.h"
#include "../../main/server/game/guns/knife.h"
#include "../../main/server/game/guns/pistol.h"
#include "../../main/server/game/guns/rocket_launcher.h"
#include "../../main/server/game/guns/chain_cannon.h"
#include "../../main/matrix.h"
#include "../../main/map.h"

int static gun_creation_test();
int static chain_cannon_check_damaged();
int static machine_gun_check_damaged();
int static pistol_check_damaged();
int static rocket_launcher_check_damaged();
int static chain_cannon_shoot_get_player_bullets_amount();
void gun_tests() {
    begin_tests("GUNS");

    print_test("Las armas se crean correctamente",
               gun_creation_test, NO_ERROR);

    print_test("El arma Chain Cannon devuelve un valor entre 1 y 10",
               chain_cannon_check_damaged, NO_ERROR);

    print_test("El arma Machine Gun devuelve un valor entre 1 y 10",
               machine_gun_check_damaged, NO_ERROR);

    print_test("El arma Pistol devuelve un valor entre 1 y 10",
               pistol_check_damaged, NO_ERROR);

    print_test("El arma Rocket Launcher devuelve un valor entre 1 y 10",
               rocket_launcher_check_damaged, NO_ERROR);
  print_test("El jugador dispara con el arma Chain Cannon y restan balas correctas",
             chain_cannon_shoot_get_player_bullets_amount, NO_ERROR);




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
  Matrix<int> matrix(10,10);
  Map game_map(matrix);
  Player player1( 0, 0, 0, game_map);
  Player player2( 5, 0, 0, game_map);
  player1.shoot(player2, chain_cannon);
  int value = player2.get_health();
  if (value>=CL::player_health-10 && value<CL::player_health) return NO_ERROR;
  return ERROR;
}

int static machine_gun_check_damaged() {
  MachineGun machine_gun;
  Matrix<int> matrix(10,10);
  Map game_map(matrix);
  Player player1( 0, 0, 0, game_map);
  Player player2( 5, 0, 0, game_map);
  player1.shoot(player2, machine_gun);
  int value = player2.get_health();
  if (value>=CL::player_health-10 && value<CL::player_health) return NO_ERROR;
  return ERROR;
}

int static pistol_check_damaged() {
  Pistol pistol;
  Matrix<int> matrix(10,10);
  Map game_map(matrix);
  Player player1( 0, 0, 0, game_map);
  Player player2( 5, 0, 0, game_map);
  player1.shoot(player2, pistol);
  int value = player2.get_health();
  if (value>=CL::player_health-10 && value<CL::player_health) return NO_ERROR;
  return ERROR;
}
int static rocket_launcher_check_damaged() {
  RocketLauncher rocket_launcher;
  Matrix<int> matrix(10,10);
  Map game_map(matrix);
  Player player1( 0, 0, 0, game_map);
  Player player2( 5, 0, 0, game_map);
  player1.shoot(player2, rocket_launcher);
  int value = player2.get_health();
  if (value>=CL::player_health-10 && value<CL::player_health) return NO_ERROR;
  return ERROR;
}

int static chain_cannon_shoot_get_player_bullets_amount() {
  ChainCannon chain_cannon;
  Matrix<int> matrix(10,10);
  Map game_map(matrix);
  Player player1( 0, 0, 0, game_map);
  Player player2( 5, 0, 0, game_map);
  player1.shoot(player2, chain_cannon);
  if (player1.has_bullets(CL::player_bullets-
      CL::chain_cannon_bullet_required)) return NO_ERROR;
  return ERROR;
}
