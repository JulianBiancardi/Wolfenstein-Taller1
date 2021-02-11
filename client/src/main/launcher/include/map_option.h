#ifndef MAP_OPTION_H
#define MAP_OPTION_H

#include <string>

class MapOption {
 private:
  std::string map_name;
  unsigned char players_total;

 public:
  MapOption();
  MapOption(const std::string& map_name, unsigned char players_total);
  ~MapOption();

  bool is_valid() const;

  void reset();

  void set_info(const std::string& map_name, unsigned char players_total);
  std::string get_map_name() const;
  unsigned char get_players_total() const;

  void print() const;
};
#endif  // MAP_OPTION_H