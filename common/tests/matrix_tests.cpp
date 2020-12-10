#include "matrix_tests.h"

#include <string>

#include "../src/main/utils/matrix.h"
#include "tests_setup.h"

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
    Matrix<int> m(5, 2);
    return NO_ERROR;
  } catch (const std::exception &e) {
    return ERROR;
  }
}

int default_int_creation_test() {
  try {
    Matrix<int> m(7, 3, 90);
    for (size_t i = 0; i < m.get_columns(); i++) {
      for (size_t j = 0; j < m.get_rows(); j++) {
        if (m(i, j) != 90) {
          return ERROR;
        }
      }
    }
    return NO_ERROR;
  } catch (const std::exception &e) {
    return ERROR;
  }
}

int empty_string_creation_test() {
  try {
    Matrix<std::string> m(5, 2);
    return NO_ERROR;
  } catch (const std::exception &e) {
    return ERROR;
  }
}

int default_string_creation_test() {
  try {
    Matrix<std::string> m(8, 3, std::string("Hola Mundo"));
    for (size_t i = 0; i < m.get_columns(); i++) {
      for (size_t j = 0; j < m.get_rows(); j++) {
        if (m(i, j) != "Hola Mundo") {
          return ERROR;
        }
      }
    }
    return NO_ERROR;
  } catch (const std::exception &e) {
    return ERROR;
  }
}

int size_test() {
  Matrix<int> m(2, 3);
  size_t x = m.get_columns();
  size_t y = m.get_rows();
  if (x == 3 && y == 2) {
    return NO_ERROR;
  }
  return ERROR;
}

int fill_test() {
  Matrix<int> m(17, 9);
  m.fill(5);
  for (size_t i = 0; i < m.get_columns(); i++) {
    for (size_t j = 0; j < m.get_rows(); j++) {
      if (m(i, j) != 5) {
        return ERROR;
      }
    }
  }
  return NO_ERROR;
}

// TODO Add test to verify RangeError being thrown