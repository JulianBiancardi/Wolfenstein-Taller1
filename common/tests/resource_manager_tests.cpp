#include "resource_manager_tests.h"

#include "../../client/src/main/resource_manager.cpp"
#include "tests_setup.h"

int static creation_test();

void resource_manager_tests() {
  begin_tests("RESOURCE MANAGER");

  print_test("El administrador de recursos se crea correctamente",
             creation_test, NO_ERROR);

  end_tests();
}

int static creation_test() {
  Window window("Test", 0, 0);
  ResourceManager res_manager(Window);
  return NO_ERROR;
}