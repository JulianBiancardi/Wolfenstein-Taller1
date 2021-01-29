#include "match_manager.h"

#include "match_manager_error.h"

MatchManager::MatchManager() : matches() {
  // TODO Delete all
  std::string mapa1("prueeeeeeeeeeeeeeeba");
  std::string mapa2("hello");
  std::string mapa3("holi");
  std::string mapa4("holu");

  create_match(mapa1);
  create_match(mapa2);
  create_match(mapa3);
  create_match(mapa4);
}

MatchManager::~MatchManager() {}

unsigned char MatchManager::next_id = 1;

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

void MatchManager::create_match(std::string& map_name) {
  std::shared_ptr<Match> new_match(new Match(map_name));
  matches.insert(std::make_pair(next_id, std::move(new_match)));
  next_id++;
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
