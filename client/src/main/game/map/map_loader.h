#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "../entities/object.h"
#include "../entities/player.h"

class MapLoader {
 private:
  std::vector<std::shared_ptr<Object>>& objects_and_players;
  std::unordered_map<unsigned int, std::shared_ptr<Object>>& objects;
  std::unordered_map<unsigned int, std::shared_ptr<Player>>& players;

  void add_object(unsigned char res_id, Point where);

 public:
  MapLoader(std::vector<std::shared_ptr<Object>>& objects_and_players,
            std::unordered_map<unsigned int, std::shared_ptr<Object>>& objects,
            std::unordered_map<unsigned int, std::shared_ptr<Player>>& players);
  ~MapLoader();

  void load_map(const std::string& map_name);
  void add_item(unsigned int item_id, unsigned char item_type, Point pos);
};

#endif
