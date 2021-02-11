#include "../include/map_option.h"

MapOption::MapOption() : map_name(""), players_total(0) {}

MapOption::MapOption(const std::string& map_name, unsigned char players_total)
    : map_name(map_name), players_total(players_total) {}

MapOption::~MapOption() {}

bool MapOption::is_valid() const {
  return (!map_name.empty() && players_total > 0);
}

void MapOption::reset() {
  map_name.clear();
  players_total = 0;
}

void MapOption::set_info(const std::string& map_name,
                         unsigned char players_total) {
  this->map_name = map_name;
  this->players_total = players_total;
}
std::string MapOption::get_map_name() const { return map_name; }
unsigned char MapOption::get_players_total() const { return players_total; }

void MapOption::print() const {}