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
  // void add_player();

  // TODO Specify which error when we have it
  /* Returns the match with the given id.
   * Throws error if the id doesn't match any match
   */
  Match& get_match(unsigned char match_id);
};

#endif
