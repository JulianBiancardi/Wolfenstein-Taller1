#include "box_mask_tests.h"

#include "../../main/collisions/box_mask.h"
#include "../../main/utils/point.h"
#include "../tests_setup.h"

int static creation_test();
int static center_test();
int static interior_test();
int static border_test();
int static exterior_test();

void box_mask_tests() {
  begin_tests("CIRCLE MASK");

  print_test("La máscara rectangular se crea correctamente", creation_test,
             NO_ERROR);
  print_test("La máscara rectangular ocupa su centro", center_test, NO_ERROR);
  print_test("La máscara rectangular ocupa puntos dentro de sus límites",
             interior_test, NO_ERROR);
  print_test("La máscara rectangular ocupa puntos en sus límites", border_test,
             NO_ERROR);
  print_test("La máscara rectangular no ocupa puntos fuera de sus límites",
             exterior_test, NO_ERROR);

  end_tests();
}

int static creation_test() {
  Point center(0, 0);
  BoxMask mask(1, 2, center);
  return NO_ERROR;
}

int static center_test() {
  Point center(0, 0);
  BoxMask mask(1, 2, center);

  Point p1(0, 0);
  if (!mask.occupies(p1)) {
    return ERROR;
  }

  return NO_ERROR;
}

int static interior_test() {
  Point center(0, 0);
  BoxMask mask(1, 2, center);

  Point p1(0, 0.4);
  Point p2(0, -0.9);
  Point p3(0, 0.01);
  Point p4(0.49, 0);
  Point p5(-0.2, -0.2);
  Point p6(0.3, -0.99);

  if (!mask.occupies(p1) || !mask.occupies(p2) || !mask.occupies(p3) ||
      !mask.occupies(p4) || !mask.occupies(p5) || !mask.occupies(p6)) {
    return ERROR;
  }
  return NO_ERROR;
}

int static border_test() {
  Point center(0, 0);
  BoxMask mask(1, 2, center);

  Point p1(0, 1);
  Point p2(0, -1);
  Point p3(0.5, 1);
  Point p4(-0.5, 0.1);
  Point p5(-0.5, 0);
  Point p6(0.3, -1);

  if (!mask.occupies(p1) || !mask.occupies(p2) || !mask.occupies(p3) ||
      !mask.occupies(p4) || !mask.occupies(p5) || !mask.occupies(p6)) {
    return ERROR;
  }
  return NO_ERROR;
}

int static exterior_test() {
  Point center(0, 0);
  BoxMask mask(1, 2, center);

  Point p1(5, 1);
  Point p2(0.6, -1);
  Point p3(0, 1.5);
  Point p4(-0.9, 0.1);
  Point p5(-0.3, 10);
  Point p6(1, 2);

  if (mask.occupies(p1) || mask.occupies(p2) || mask.occupies(p3) ||
      mask.occupies(p4) || mask.occupies(p5) || mask.occupies(p6)) {
    return ERROR;
  }
  return NO_ERROR;
}
