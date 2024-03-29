#ifndef MATCH_MANAGER_H
#define MATCH_MANAGER_H

#include <memory>
#include <unordered_map>

#include "match.h"

class MatchManager {
 private:
  unsigned char next_id;
  std::unordered_map<unsigned char, std::shared_ptr<Match>> matches;
  bool match_exists(unsigned char match_id);

 public:
  MatchManager();

  ~MatchManager();

  /* Returns a reference to the matches */
  const std::unordered_map<unsigned char, std::shared_ptr<Match>>&
  get_matches();

  /* Returns the match with the given id.
   * Throws MatchManagerError if the id doesn't match any match.
   */
  Match& get_match(unsigned char match_id);

  /* Creates a new match */
  unsigned char create_match(unsigned int host_id, std::string& map_name);

  /* Finds and returns the match id of the player */
  unsigned char find_match_of_player(unsigned int player_id);

  /* Deletes a match.
   * Throws MatchManagerError if the id doesn't match any match.
   */
  void delete_match(unsigned char match_id);
};

#endif
