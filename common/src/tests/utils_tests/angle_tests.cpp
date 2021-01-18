#include "angle_tests.h"

#include <cmath>
#include <random>

#include "../../main/utils/angle.h"
#include "../tests_setup.h"

int static creation_test();
int static create_and_normalize_test();
int static static_normalize_test();

void angle_tests() {
  begin_tests("ANGLE");

  print_test("Un ángulo se crea correctamente", creation_test, NO_ERROR);
  print_test("Un ángulo se normaliza al crearse", create_and_normalize_test,
             NO_ERROR);
  print_test("Se puede normalizar cualquier ángulo con el método de clase",
             static_normalize_test, NO_ERROR);

  end_tests();
}

int static creation_test() {
  Angle a1(1);
  Angle a2(0);
  Angle a3(5);
  Angle a4(-1);
  Angle a5(0.1);
  Angle a6(-0.7);
  Angle a7(M_PI);
  return NO_ERROR;
}

int static create_and_normalize_test() {
  std::default_random_engine generator;
  std::uniform_real_distribution<double> dist(-10, 10);
  for (int i = 0; i < 10; i++) {
    Angle a(dist(generator));
    if (a.to_double() >= 2 * M_PI || a.to_double() < 0) {
      return ERROR;
    }
  }
  return NO_ERROR;
}

int static static_normalize_test() {
  std::default_random_engine generator;
  std::uniform_real_distribution<double> dist(-10, 10);
  for (int i = 0; i < 10; i++) {
    double a = Angle::normalize(dist(generator));
    if (a >= 2 * M_PI || a < 0) {
      return ERROR;
    }
  }
  return NO_ERROR;
}
