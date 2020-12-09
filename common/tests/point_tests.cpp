#include "point_tests.h"

#include <cmath>
#include "../src/main/utils/point.h"
#include "tests_setup.h"

int static point_creation_test();
int static get_x_test();
int static get_y_test();
int static basic_distance_test();
int static extreme_distance_test();

void point_tests() {
  begin_tests("POINT");

  print_test("El punto se crea correctamente", point_creation_test, NO_ERROR);
  print_test("El punto devuelve su coordenada X correctamente", get_x_test,
             NO_ERROR);
  print_test("El punto devuelve su coordenada Y correctamente", get_y_test,
             NO_ERROR);
  print_test("Se calcula correctamente la distancia entre 2 puntos",
             basic_distance_test, NO_ERROR);
  print_test("Se calcula correctamente la distancia entre 2 puntos muy lejanos",
             extreme_distance_test, NO_ERROR);

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

int static basic_distance_test() {
  Point a(1, 6);
  Point b(-9, 10);
  double distance = Point::distance(a, b);
  double real_distance = sqrt(116);
  if (distance != real_distance) {
    return ERROR;
  }
  return NO_ERROR;
}

int static extreme_distance_test() {
  Point a(1073741823, 0);
  Point b(-1073741823, 0);
  double distance = Point::distance(a, b);
  unsigned long long real_norm = (unsigned long long) 4611686009837453316;
  double real_distance = sqrt(real_norm);
  if (distance != real_distance) {
    return ERROR;
  }
  return NO_ERROR;
}