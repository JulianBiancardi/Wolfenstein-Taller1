#include "match_tests.h"
#include "player_test.h"
#include "bot_test.h"

int main(int argc, char** argv) {
  player_tests();
  match_tests();
  bot_tests();
  return 0;
}
