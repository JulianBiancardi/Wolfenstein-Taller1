#include "match_manager.h"

MatchManager::MatchManager() : matches() {}

MatchManager::~MatchManager() {}

bool MatchManager::match_exists(unsigned char match_id) {
  return matches.find(match_id) != matches.end();
}

void MatchManager::move_player(unsigned char match_id, unsigned char player_id,
                               unsigned char dir) {
  if (match_exists(match_id)) {
    matches[match_id].move_player(player_id, dir);
  } else {
    throw 1;  // TODO Throw error
  }
}

void MatchManager::change_gun(unsigned char match_id, unsigned char player_id,
                              unsigned char gun_id) {
  if (match_exists(match_id)) {
    matches[match_id].change_gun(player_id, gun_id);
  } else {
    throw 1;  // TODO Throw error
  }
}