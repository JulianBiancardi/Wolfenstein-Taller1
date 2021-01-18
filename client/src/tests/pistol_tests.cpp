#include "pistol_tests.h"

#include <stdio.h>  // TODO DELETE

#include "../../../common/src/main/utils/matrix.h"
#include "../main/guns/hit.h"
#include "../main/guns/pistol.h"
#include "../main/map.h"
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

void static load_basic_matrix(Matrix<int>& m) {
  for (int i = 0; i < 5; i++) {
    m(i, 0) = 1;
    m(i, 4) = 1;
    m(0, i) = 1;
    m(4, i) = 1;
  }
}

void static load_huge_matrix(Matrix<int>& m) {
  for (int i = 0; i < 100; i++) {
    m(i, 0) = 1;
    m(i, 99) = 1;
    m(0, i) = 1;
    m(99, i) = 1;
  }
}

int static creation_test() {
  Pistol pistol();
  return NO_ERROR;
}

int static angle_zero_test() {
  Matrix<int> m(5, 5, 0);
  load_basic_matrix(m);
  Map map(m);

  Ray pos1(1.5, 1.5, 0);
  Player shooter(pos1);

  Ray pos2(3.5, 1.5, 0);
  Player objective(pos2);

  Pistol* pistol = new Pistol();
  shooter.add_gun(1, pistol);
  shooter.set_gun(1);

  map.add_player(&shooter);
  map.add_player(&objective);

  Hit hit = shooter.shoot(map);

  if (hit.get_object_id() != objective.get_id()) {
    return ERROR;
  }
  return NO_ERROR;
}

int static small_angle_test() {
  Matrix<int> m(5, 5, 0);
  load_basic_matrix(m);
  Map map(m);

  Ray pos1(1.5, 1.5, 0);
  Player shooter(pos1);

  Ray pos2(2.5, 1.8, 0);
  Player objective(pos2);

  Pistol* pistol = new Pistol();
  shooter.add_gun(1, pistol);
  shooter.set_gun(1);

  map.add_player(&shooter);
  map.add_player(&objective);

  Hit hit = shooter.shoot(map);

  if (hit.get_object_id() != objective.get_id()) {
    return ERROR;
  }
  return NO_ERROR;
}

int static close_test() {
  Matrix<int> m(5, 5, 0);
  load_basic_matrix(m);
  Map map(m);

  Ray pos1(2.5, 2.5, -0.785398);
  Player shooter(pos1);

  Ray pos2(3.5, 3.5, 0);
  Player objective(pos2);

  Pistol* pistol = new Pistol();
  shooter.add_gun(1, pistol);
  shooter.set_gun(1);

  map.add_player(&shooter);
  map.add_player(&objective);

  Hit hit = shooter.shoot(map);

  if (hit.get_object_id() != objective.get_id()) {
    return ERROR;
  }
  return NO_ERROR;
}

int static far_test() {
  Matrix<int> m(100, 100, 0);
  load_huge_matrix(m);
  Map map(m);

  Ray pos1(1.5, 1.5, -0.785398);
  Player shooter(pos1);

  Ray pos2(15.0, 15.0, 0);
  Player objective(pos2);

  Pistol* pistol = new Pistol();
  shooter.add_gun(1, pistol);
  shooter.set_gun(1);

  map.add_player(&shooter);
  map.add_player(&objective);

  bool hit_flag = false;
  bool miss_flag = false;
  for (int i = 0; i < 10; i++) {
    Hit hit = shooter.shoot(map);

    if (hit.get_object_id() == objective.get_id()) {
      hit_flag = true;
    } else if (hit.get_object_id() == -1) {
      miss_flag = true;
    }
  }

  // It is expected to both hit and miss and such distances
  // The distance is arbitrary and hitting or missing depends on the hitbox
  // In case of ERROR in this test, adjust distance of objective
  if (hit_flag && miss_flag) {
    return NO_ERROR;
  }
  return ERROR;
}