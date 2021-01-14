#include "resource_manager_tests.h"
#include "resource_tests.h"
#include "gun_tests.h"
int main(int argc, char **argv) {

  gun_tests();

  resource_tests();
  // resource_manager_tests();
  return 0;
}