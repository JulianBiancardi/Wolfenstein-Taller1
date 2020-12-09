#include "resource_tests.h"

#include "../../client/src/main/resource.h"
#include "tests_setup.h"

int static creation_test();
int static created_unloaded_test();

void resource_tests() {
  begin_tests("RESOURCE");

  print_test("El recurso se crea correctamente", creation_test, NO_ERROR);
  print_test("El recurso se crea sin estar cargado", created_unloaded_test,
             NO_ERROR);

  end_tests();
}

int static creation_test() {
  Resource res0(0);
  Resource res1(1);

  return NO_ERROR;
}

int static created_unloaded_test() {
  Resource res(1);
  if (res.is_loaded()) {
    return ERROR;
  }
  return NO_ERROR;
}