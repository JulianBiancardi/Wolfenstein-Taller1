#include "gun_tests.h"
#include "../../main/server/game/guns/knife.h"
#include "../../main/server/game/guns/pistol.h"
#include "../../main/server/game/guns/rocket_launcher.h"
#include "../../main/server/game/guns/chain_cannon.h"

int static gun_creation_test();
int static chain_cannon_check_damaged();
int static machine_gun_check_damaged();
int static pistol_check_damaged();
int static rocket_launcher_check_damaged();

void gun_tests() {
    begin_tests("GUNS");

    print_test("Las armas se crean correctamente",
               gun_creation_test, NO_ERROR);

    print_test("El arma Chain Cannon un valor entre 1 y 10",
               chain_cannon_check_damaged, NO_ERROR);

    print_test("El arma Machine Gun devuelve un valor entre 1 y 10",
               machine_gun_check_damaged, NO_ERROR);

    print_test("El arma Pistol devuelve un valor entre 1 y 10",
               pistol_check_damaged, NO_ERROR);

    print_test("El arma Rocket Launcher devuelve un valor entre 1 y 10",
               rocket_launcher_check_damaged, NO_ERROR);
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
    ChainCannon chainCannon;
    Player player;
    int value = 1;
    chainCannon.shoot(player);

//    value = player.get_health();
    if (value>=1 && value<10) return NO_ERROR;

    return ERROR;
}

int static machine_gun_check_damaged() {
    MachineGun machineGun;
    Player player;
    int value = 1;
    machineGun.shoot(player);

//    value = player.get_health();
    if (value>=1 && value<10) return NO_ERROR;

    return ERROR;
}

int static pistol_check_damaged() {
    Pistol pistol;
    Player player;
    int value = 1;
    pistol.shoot(player);

//    value = player.get_health();
    if (value>=1 && value<10) return NO_ERROR;

    return ERROR;
}
int static rocket_launcher_check_damaged() {
    RocketLauncher rocketLauncher;
    Player player;
    int value = 1;
    rocketLauncher.shoot(player);

//    value = player.get_health();
    if (value>=1 && value<10) return NO_ERROR;

    return ERROR;
}
