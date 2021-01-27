#include "match.h"

Match::Match() : match_id(-1), players_joined(0), players_total(0), status(0) {}

Match::Match(unsigned char match_id, char* map_name,
             unsigned char players_joined, unsigned char players_total,
             unsigned char status)
    : match_id(match_id),
      players_joined(players_joined),
      players_total(players_total),
      status(status) {
  memcpy(this->map_name, map_name, strlen(map_name));
}

unsigned char Match::get_match_id() const { return match_id; }
unsigned char Match::get_players_joined() const { return players_joined; }
unsigned char Match::get_players_total() const { return players_total; }
unsigned char Match::get_status() const { return status; }

Match::~Match() {}
