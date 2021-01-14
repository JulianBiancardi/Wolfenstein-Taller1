#include "ray_tests.h"

#include "../../main/utils/ray.h"
#include "../tests_setup.h"

int static ray_creation_test();
int static ray_origin_test();
int static ray_angle_test();

void ray_tests() {
  begin_tests("RAY");

  print_test("El Rayo se crea correctamente", ray_creation_test, NO_ERROR);
  print_test("El Rayo devuelve correctamente su origen", ray_origin_test,
             NO_ERROR);
  print_test("El Rayo devuelve correctamente su angulo", ray_angle_test,
             NO_ERROR);

  end_tests();
}

int static ray_creation_test() {
  try {
    Ray a(1, 3, 5);
    Ray b(7, -1, -2);
    Ray c(0, 10, 0);

    Point p(3, 7);
    Point q(-5, 4);
    Point r(2, -6);
    Ray d(p, 0.1);
    Ray e(q, 3.14);
    Ray f(r, 1.04);
  } catch (...) {
    return ERROR;
  }
  return NO_ERROR;
}

int static ray_origin_test() {
  Ray a(9, 1, 0.5);
  if (a.get_origin().getX() != 9) {
    return ERROR;
  }
  if (a.get_origin().getY() != 1) {
    return ERROR;
  }
  return NO_ERROR;
}

int static ray_angle_test() {
  Ray a(-1, 10, 0.8);
  if (a.get_angle() != 0.8) {
    return NO_ERROR;
  }
  return NO_ERROR;
}