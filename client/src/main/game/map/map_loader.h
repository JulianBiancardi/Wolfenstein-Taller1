#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "../entities/drawable.h"
#include "../entities/items/item.h"
#include "../entities/object.h"
#include "../entities/player.h"

class MapLoader {
 private:
  unsigned int next_id;

  std::vector<std::weak_ptr<Object>>& drawables;
  std::vector<std::weak_ptr<IdentifiableObject>>& players_shootable;
  std::vector<std::shared_ptr<Object>>& ambient_objects;
  std::unordered_map<unsigned int, std::shared_ptr<Item>>& items;
  std::unordered_map<unsigned int, std::shared_ptr<Player>>& players;

  void add_object(const Ray& position, unsigned int resource_id);

 public:
  MapLoader(std::vector<std::weak_ptr<Object>>& drawables,
            std::vector<std::weak_ptr<IdentifiableObject>>& players_shootable,
            std::vector<std::shared_ptr<Object>>& ambient_objects,
            std::unordered_map<unsigned int, std::shared_ptr<Item>>& items,
            std::unordered_map<unsigned int, std::shared_ptr<Player>>& players);
  ~MapLoader();

  void load_map(const std::string& map_name);
  void add_player(const Ray& position, unsigned int player_id);
  void add_item(const Ray& position, unsigned int resource_id);
};

#endif
