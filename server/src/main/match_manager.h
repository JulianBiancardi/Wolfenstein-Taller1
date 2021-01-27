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

  /* Returns a reference to the matches */
  const std::unordered_map<unsigned char, Match>& get_matches();

  /* Returns the match with the given id.
   * Throws MatchManagerError if the id doesn't match any match.
   */
  Match& get_match(unsigned char match_id);

  /* Creates a new match */
  void create_match();

  /* Finds and returns the match id of the player */
  unsigned char find_match_of_player(unsigned int player_id);

  /* Adds a player to a match */
  // void add_player();
};

#endif
