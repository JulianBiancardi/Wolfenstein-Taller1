#include "pistol_tests.h"

#include "../../../common/src/main/utils/matrix.h"
#include "../main/guns/hit.h"
#include "../main/guns/pistol.h"
#include "../map.h"
#include "tests_setup.h"

int static creation_test();
int static angle_zero_test();
int static small_angle_test();
int static close_test();
int static far_test();

void pistol_tests() {
  begin_tests("PISTOL");

  print_test("La pistola se crea correctamente", creation_test, NO_ERROR);
  print_test(
      "La pistola detecta correctamente pegarle a alguien formando angulo 0",
      angle_zero_test, NO_ERROR);
  print_test(
      "La pistola detecta correctamente pegarle a alguien formando un pequeño "
      "ángulo",
      small_angle_test, NO_ERROR);
  print_test("La pistola detecta correctamente pegarle a alguien muy cerca",
             close_test, NO_ERROR);
  print_test("La pistola detecta correctamente pegarle a alguien muy lejos",
             far_test, NO_ERROR);

  end_tests();
}

int static creation_test() {
  Pistol pistol();
  return NO_ERROR;
}

int static angle_zero_test() {
  Matrix<int> m(5, 5, 0);
  Map map(m);

  Ray pos1(0, 0, 0);
  Player shooter(pos1);

  Ray pos2(1, 0, 0);
  Player objective(pos2);

  Pistol* pistol = new Pistol();
  shooter.add_gun(1, pistol);
  shooter.set_gun(1);

  map.add_player(&shooter);
  map.add_player(&objective);

  Hit hit = shooter.shoot(map);

  if (hit.get_object_id() == objective.get_id()) {
    return ERROR;
  }
  return NO_ERROR;
}