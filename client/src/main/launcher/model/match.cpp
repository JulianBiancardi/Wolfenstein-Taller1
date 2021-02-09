#include "../include/match.h"

#include <iostream>  //TODO DELETE

#define INVALID_ID 0
#define IN_GAME true
#define WAITING false

Match::Match()
    : match_id(INVALID_ID),
      map_name(""),
      players_joined(0),
      players_total(0),
      status(WAITING) {}

Match::Match(unsigned char match_id, const char* map_name,
             unsigned char players_joined, unsigned char players_total,
             bool status)
    : match_id(match_id),
      players_joined(players_joined),
      players_total(players_total),
      status(status) {
  memcpy(this->map_name, map_name, strlen(map_name) + 1);
}

bool Match::is_running() const { return (status == IN_GAME); }

bool Match::is_valid() const { return match_id != INVALID_ID; }

void Match::copy(const Match& other) {
  this->match_id = other.match_id;
  memcpy(this->map_name, other.map_name, strlen(other.map_name) + 1);
  this->players_joined = other.players_joined;
  this->players_total = other.players_total;
  this->status = other.status;
}
void Match::reset() {
  match_id = INVALID_ID;
  map_name[0] = '\0';
}

void Match::set_match_id(unsigned char id) { match_id = id; }

void Match::set_map_name(const char* map_name) {
  memcpy(this->map_name, map_name, strlen(map_name) + 1);
}

unsigned char Match::get_match_id() const { return match_id; }

const char* Match::get_map_name() const { return map_name; }

unsigned char Match::get_players_joined() const { return players_joined; }

unsigned char Match::get_players_total() const { return players_total; }

bool Match::get_status() const { return status; }

void Match::print() const {
  printf("Match_id: %u\n", match_id);
  printf("Map_name: %s\n", map_name);
}

Match::~Match() {}
