#include "match_manager.h"

#include "match_manager_error.h"

#define MATCHES_CAPACITY 255

MatchManager::MatchManager() : next_id(1), matches() {}

MatchManager::~MatchManager() {}

bool MatchManager::match_exists(unsigned char match_id) {
  return matches.find(match_id) != matches.end();
}

const std::unordered_map<unsigned char, std::shared_ptr<Match>>&
MatchManager::get_matches() {
  return matches;
}

Match& MatchManager::get_match(unsigned char match_id) {
  if (!match_exists(match_id)) {
    throw MatchManagerError("Failed to get match. The match %u doesn't exist.",
                            match_id);
  }

  return *(matches[match_id]);
}

unsigned char MatchManager::create_match(unsigned int host_id,
                                         std::string& map_name) {
  if (matches.size() < MATCHES_CAPACITY) {
    std::shared_ptr<Match> new_match(new Match(host_id, next_id, map_name));
    matches.insert(std::make_pair(next_id, std::move(new_match)));
    next_id++;
    return next_id - 1;
  } else {
    return 0;
  }
}

unsigned char MatchManager::find_match_of_player(unsigned int player_id) {
  std::unordered_map<unsigned char, std::shared_ptr<Match>>::iterator iter;
  for (iter = matches.begin(); iter != matches.end(); iter++) {
    Match& match = *(iter->second);
    if (match.player_exists(player_id)) {
      return match.get_id();
    }
  }
  return 0;
}
