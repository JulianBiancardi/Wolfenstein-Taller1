#include "bot_test.h"
#include "match_tests.h"
#include "player_test.h"
#include "clock/clock_tests.h"

int main(int argc, char** argv) {
  match_tests();
  player_tests();
  bot_tests();
  clock_tests();
  return 0;
}
