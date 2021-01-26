#include "match.h"

Match::Match(unsigned char match_id, char* map_name,
             unsigned char players_joined, unsigned char players_total,
             unsigned char status)
    : match_id(match_id),
      players_joined(players_joined),
      players_total(players_total),
      status(status) {
  memcpy(this->map_name, map_name, strlen(map_name));
}

Match::~Match() {}
