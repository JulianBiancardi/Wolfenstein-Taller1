#include "circle_mask_tests.h"

#include "../../main/collisions/circle_mask.h"
#include "../../main/utils/point.h"
#include "../tests_setup.h"

int static creation_test();
int static center_test();
int static interior_test();
int static border_test();
int static exterior_test();

void circle_mask_tests() {
  begin_tests("CIRCLE MASK");

  print_test("La máscara circular se crea correctamente", creation_test,
             NO_ERROR);
  print_test("La máscara circular ocupa su centro", center_test, NO_ERROR);
  print_test(
      "La máscara circular ocupa puntos dentro de su circunferencia límite",
      interior_test, NO_ERROR);
  print_test("La máscara circular ocupa puntos en su circunferencia límite",
             border_test, NO_ERROR);
  print_test("La máscara circular no ocupa puntos fuera de su circunferencia",
             exterior_test, NO_ERROR);

  end_tests();
}

int static creation_test() {
  Point center(0, 0);
  CircleMask mask(1, center);
  return NO_ERROR;
}

int static center_test() {
  Point center(0, 0);
  CircleMask mask(1, center);

  Point center_p(0, 0);
  if (!mask.occupies(center_p)) {
    return ERROR;
  }
  return NO_ERROR;
}

int static interior_test() {
  Point center(0, 0);
  CircleMask mask(1, center);

  Point p1(-0.1, 0.5);
  Point p2(-0.6, -0.79);
  Point p3(0.8, 0.0);
  Point p4(0, 0.3);
  Point p5(-0.2, 0.2);

  if (!mask.occupies(p1)) {
    return ERROR;
  }
  if (!mask.occupies(p2)) {
    return ERROR;
  }
  if (!mask.occupies(p3)) {
    return ERROR;
  }
  if (!mask.occupies(p4)) {
    return ERROR;
  }
  if (!mask.occupies(p5)) {
    return ERROR;
  }
  return NO_ERROR;
}

int static border_test() {
  Point center(0, 0);
  CircleMask mask(1, center);

  Point p1(0, 1);
  Point p2(0, -1);
  Point p3(1, 0);
  Point p4(-1, 0);

  if (!mask.occupies(p1) || !mask.occupies(p2) || !mask.occupies(p3) ||
      !mask.occupies(p4)) {
    return ERROR;
  }
  return NO_ERROR;
}

int static exterior_test() {
  Point center(0, 0);
  CircleMask mask(1, center);

  Point p1(0, 2);
  Point p2(0, 1.1);
  Point p3(1, 1);
  Point p4(0, -1.5);

  if (mask.occupies(p1) || mask.occupies(p2) || mask.occupies(p3) ||
      mask.occupies(p4)) {
    return ERROR;
  }
  return NO_ERROR;
}
