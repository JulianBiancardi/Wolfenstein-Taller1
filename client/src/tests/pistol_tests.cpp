#include "pistol_tests.h"

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
  Map map();

  map.add_player()
}