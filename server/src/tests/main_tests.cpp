#include "bot_test.h"
#include "player_test.h"
#include "clock/clock_tests.h"

int main(int argc, char** argv) {
  bot_tests();
  player_tests();
  clock_tests();
  return 0;
}
