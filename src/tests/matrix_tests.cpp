#include "matrix_tests.h"

#include <string>

#include "../main/matrix.h"
#include "tests_setup.h"

#define NO_ERROR 0
#define ERROR 1

int empty_int_creation_test();
int default_int_creation_test();
int empty_string_creation_test();
int default_string_creation_test();
int size_test();
int fill_test();

void matrix_tests() {
  begin_tests("MATRIX");

  print_test("La Matriz de int se crea vacía con éxito",
             empty_int_creation_test, NO_ERROR);
  print_test("La Matriz de int se crea con valores con éxito",
             default_int_creation_test, NO_ERROR);
  print_test("La Matriz de std::string se crea vacía con éxito",
             empty_int_creation_test, NO_ERROR);
  print_test("La Matriz de std::string se crea con valores con éxito",
             default_int_creation_test, NO_ERROR);
  print_test("La Matriz devuelve correctamente sus dimensiones", size_test,
             NO_ERROR);
  print_test("La Matriz se llena correctamente", fill_test, NO_ERROR);
  end_tests();
}

int empty_int_creation_test() {
  try {
    Matrix<int, 2, 5> m;
    return NO_ERROR;
  } catch (const std::exception& e) {
    return ERROR;
  }
}

int default_int_creation_test() {
  try {
    Matrix<int, 3, 7> m(90);
    for (int i = 0; i < m.sizeX(); i++) {
      for (int j = 0; j < m.sizeY(); j++) {
        if (m(i, j) != 90) {
          return ERROR;
        }
      }
    }
    return NO_ERROR;
  } catch (const std::exception& e) {
    return ERROR;
  }
}

int empty_string_creation_test() {
  try {
    Matrix<std::string, 2, 5> m;
    return NO_ERROR;
  } catch (const std::exception& e) {
    return ERROR;
  }
}

int default_string_creation_test() {
  try {
    Matrix<std::string, 3, 7> m(std::string("Hola Mundo"));
    for (int i = 0; i < m.sizeX(); i++) {
      for (int j = 0; j < m.sizeY(); j++) {
        if (m(i, j) != "Hola Mundo") {
          return ERROR;
        }
      }
    }
    return NO_ERROR;
  } catch (const std::exception& e) {
    return ERROR;
  }
}

int size_test() {
  Matrix<int, 2, 3> m;
  size_t x = m.sizeX();
  size_t y = m.sizeY();
  if (x == 2 && y == 3) {
    return NO_ERROR;
  }
  return ERROR;
}

int fill_test() {
  Matrix<int, 9, 17> m;
  m.fill(5);
  for (int i = 0; i < m.sizeX(); i++) {
    for (int j = 0; j < m.sizeY(); j++) {
      printf("[%d, %d] : %d\n", i, j, m(i, j));
      if (m(i, j) != 5) {
        return ERROR;
      }
    }
  }
  return NO_ERROR;
}