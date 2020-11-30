#include "point_tests.h"

#include "../main/point.h"
#include "tests_setup.h"

int static point_creation_test();
int static get_x_test();
int static get_y_test();

void point_tests() {
  begin_tests("POINT");

  print_test("El punto se crea correctamente", point_creation_test, NO_ERROR);
  print_test("El punto devuelve su coordenada X correctamente", get_x_test,
             NO_ERROR);
  print_test("El punto devuelve su coordenada Y correctamente", get_y_test,
             NO_ERROR);
  end_tests();
}

int static point_creation_test() {
  Point point0(2, 3);
  Point point1(4, 5);
  Point point2(0, 0);
  Point point3(-1, 5);
  Point point4(-9, -2);
  return NO_ERROR;
}

int static get_x_test() {
  Point point0(2, 3);
  Point point1(4, 5);
  Point point2(0, 0);
  Point point3(-1, 5);
  Point point4(-9, -2);

  if (point0.getX() != 2 || point1.getX() != 4 || point2.getX() != 0 ||
      point3.getX() != -1 || point4.getX() != -9) {
    return ERROR;
  }
  return NO_ERROR;
}

int static get_y_test() {
  Point point0(2, 3);
  Point point1(4, 5);
  Point point2(0, 0);
  Point point3(-1, 5);
  Point point4(-9, -2);

  if (point0.getY() != 3 || point1.getY() != 5 || point2.getY() != 0 ||
      point3.getY() != 5 || point4.getY() != -2) {
    return ERROR;
  }
  return NO_ERROR;
}
