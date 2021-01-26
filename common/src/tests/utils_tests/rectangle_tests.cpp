#include "rectangle_tests.h"

#include "../../main/utils/rectangle.h"
#include "../tests_setup.h"

int static creation_test();
int static borders_test();
int static width_test();
int static height_test();

void rectangle_tests() {
  begin_tests("Rectangle");

  print_test("El rectangulo se crea correctamente", creation_test, NO_ERROR);
  print_test("El rectangulo devuelve correctamente sus bordes", borders_test,
             NO_ERROR);
  print_test("El rectangulo devuelve correctamente su ancho", width_test,
             NO_ERROR);
  print_test("El rectangulo devuelve correctamente su alto", height_test,
             NO_ERROR);

  end_tests();
}

int static creation_test() {
  Rectangle rect1(0, 0, 1, 1);
  Rectangle rect2(2, 5, 1, 9);
  Rectangle rect3(0, 9, 2, 3);
  return NO_ERROR;
}

int static borders_test() {
  Rectangle rect(2, 5, 1, 9);
  size_t top = rect.get_top();
  size_t bot = rect.get_bot();
  size_t left = rect.get_left();
  size_t right = rect.get_right();

  if (top != 2 || bot != 5 || left != 1 || right != 9) {
    return ERROR;
  }
  return NO_ERROR;
}

int static width_test() {
  Rectangle rect(2, 5, 1, 9);
  size_t width = rect.get_width();
  if (width != 8) {
    return ERROR;
  }
  return NO_ERROR;
}

int static height_test() {
  Rectangle rect(2, 5, 1, 9);
  size_t height = rect.get_height();
  if (height != 3) {
    return ERROR;
  }
  return NO_ERROR;
}