#include "leaderboard.h"

#include <utility>

Leaderboard::Leaderboard(std::vector<std::shared_ptr<Player>>&& players)
    : players(std::move(players)) {}

Leaderboard::~Leaderboard() = default;

bool compare_by_kills(const std::shared_ptr<Player>& p1,
                      const std::shared_ptr<Player>& p2) {
  return p1->get_kills() < p2->get_kills();
}

void Leaderboard::show() {
  std::sort(players.begin(), players.end(), compare_by_kills);
}
