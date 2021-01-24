#include "match_manager.h"

MatchManager::MatchManager() : matches() {}

MatchManager::~MatchManager() {}

bool MatchManager::match_exists(unsigned char match_id) {
  return matches.find(match_id) != matches.end();
}

Match& MatchManager::get_match(unsigned char match_id) {
  if (!match_exists(match_id)) {
    throw 1;  // TODO Throw error
  }

  return matches[match_id];
}
