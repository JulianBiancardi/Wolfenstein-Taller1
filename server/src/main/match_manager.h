#ifndef MATCH_MANAGER_H
#define MATCH_MANAGER_H

#include <unordered_map>

#include "game/match.h"

class MatchManager {
 private:
  std::unordered_map<int, Match> matches;

 public:
  MatchManager();
  ~MatchManager();

  void create_match();
  void add_player();
};

#endif
