#ifndef MATCH_H
#define MATCH_H

#include <cstring>

#define INVALID_ID 0
#define MAP_NAME_MAX_SIZE \
  64  // TODO Move somewhere else. Also check in launcher.h since i also put it
      // there

class Match {
 private:
  unsigned char match_id;
  char map_name[MAP_NAME_MAX_SIZE];
  unsigned char players_joined;
  unsigned char players_total;
  bool status;

 public:
  Match();
  Match(unsigned char match_id, const char* map_name,
        unsigned char players_joined, unsigned char players_total, bool status);

  bool is_running() const;
  bool is_valid() const;

  void reset();

  void set_match_id(unsigned char id);
  void set_map_name(const char* map_name);
  unsigned char get_match_id() const;
  const char* get_map_name() const;
  unsigned char get_players_joined() const;
  unsigned char get_players_total() const;
  bool get_status() const;

  void print() const;

  ~Match();
};
#endif