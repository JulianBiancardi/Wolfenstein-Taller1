#include "game_test/gun_tests.h"
#include "game_test/player_test.h"
#include "matrix_tests.h"
#include "point_tests.h"
#include "ray_tests.h"
#include "rectangle_tests.h"
#include "resource_tests.h"

int main(int argc, char** argv) {
  matrix_tests();
  point_tests();
  ray_tests();
  rectangle_tests();
  resource_tests();
  gun_tests();
  player_tests();
  return 0;
}