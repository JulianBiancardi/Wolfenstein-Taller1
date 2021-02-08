#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "../../../common/src/main/object.h"
#include "player.h"

class MapLoader {
 private:
  std::vector<std::shared_ptr<Object>> objects_and_players;
  std::unordered_map<unsigned int, std::shared_ptr<Object>> objects;
  std::unordered_map<unsigned int, std::shared_ptr<Player>> players;

  void add_object(unsigned char res_id, Point where);

 public:
  MapLoader(std::vector<std::shared_ptr<Object>>& objects_and_players,
            std::unordered_map<unsigned int, std::shared_ptr<Object>>& objects,
            std::unordered_map<unsigned int, std::shared_ptr<Player>>& players);
  ~MapLoader();

  void load_map(const std::string& map_name);
};

#endif
