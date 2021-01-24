#ifndef MATCH_MANAGER_H
#define MATCH_MANAGER_H

#include <unordered_map>

#include "game/match.h"

class MatchManager {
 private:
  std::unordered_map<unsigned char, Match> matches;
  bool match_exists(unsigned char match_id);

 public:
  MatchManager();

  ~MatchManager();

  /* Creates a new match */
  void create_match();

  /* Adds a player to a match */
  void add_player();

  /* Move a player in the given match */
  void move_player(unsigned char match_id, unsigned char player_id,
                   unsigned char dir);

  /* Change the gun of the player in the given match */
  void change_gun(unsigned char match_id, unsigned char player_id,
                  unsigned char gun_id);
};

#endif
