#include "match_manager.h"

#include "match_manager_error.h"

MatchManager::MatchManager() : matches() {}

MatchManager::~MatchManager() {}

bool MatchManager::match_exists(unsigned char match_id) {
  return matches.find(match_id) != matches.end();
}

const std::unordered_map<unsigned char, Match>& MatchManager::get_matches() {
  return matches;
}

Match& MatchManager::get_match(unsigned char match_id) {
  if (!match_exists(match_id)) {
    throw MatchManagerError("Failed to get match. The match %u doesn't exist.",
                            match_id);
  }

  return matches[match_id];
}

unsigned char MatchManager::find_match_of_player(unsigned int player_id) {
  std::unordered_map<unsigned char, Match>::iterator iter;
  for (iter = matches.begin(); iter != matches.end(); iter++) {
    Match& match = iter->second;
    if (match.player_exists(player_id)) {
      return match.get_id();
    }
  }
  return 0;
}
