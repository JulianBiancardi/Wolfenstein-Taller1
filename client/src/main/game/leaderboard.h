#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <vector>
#include <memory>

#include "entities/player.h"

class Leaderboard {
 private:
  std::vector<std::shared_ptr<Player>> players;

 public:
  Leaderboard(std::vector<std::shared_ptr<Player>>&& players);
  ~Leaderboard();

  void show();
};

#endif
