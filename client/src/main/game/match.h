#ifndef MATCH_H
#define MATCH_H

#include <cstring>

#define MAP_NAME_MAX_SIZE \
  64  // TODO Move somewhere else. Also check in launcher.h since i also put it
      // there

class Match {
 private:
  unsigned char match_id;
  char map_name[MAP_NAME_MAX_SIZE];
  unsigned char players_joined;
  unsigned char players_total;
  unsigned char status;

 public:
  Match();
  Match(unsigned char match_id, char* map_name, unsigned char players_joined,
        unsigned char players_total, unsigned char status);

  unsigned char get_match_id() const;
  unsigned char get_players_joined() const;
  unsigned char get_players_total() const;
  unsigned char get_status() const;

  ~Match();
};
#endif