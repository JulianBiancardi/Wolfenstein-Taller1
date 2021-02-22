#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../entities/doors/base_door.h"
#include "../entities/drawable.h"
#include "../entities/items/item.h"
#include "../entities/object.h"
#include "../entities/player.h"

class MapLoader {
 private:
  std::vector<std::weak_ptr<Object>>& drawables;
  std::vector<std::weak_ptr<IdentifiableObject>>& players_shootable;
  std::vector<std::shared_ptr<Object>>& ambient_objects;
  std::unordered_map<unsigned int, std::shared_ptr<Item>>& items;
  std::unordered_map<unsigned int, std::shared_ptr<Player>>& players;
  std::unordered_map<std::pair<unsigned int, unsigned int>,
                     std::unique_ptr<BaseDoor>, PairHasher>& doors;

  void add_door(unsigned int x, unsigned int y, unsigned int resource_id);
  void add_object(const Ray& position, unsigned int resource_id);

 public:
  MapLoader(std::vector<std::weak_ptr<Object>>& drawables,
            std::vector<std::weak_ptr<IdentifiableObject>>& players_shootable,
            std::vector<std::shared_ptr<Object>>& ambient_objects,
            std::unordered_map<unsigned int, std::shared_ptr<Item>>& items,
            std::unordered_map<unsigned int, std::shared_ptr<Player>>& players,
            std::unordered_map<std::pair<unsigned int, unsigned int>,
                               std::unique_ptr<BaseDoor>, PairHasher>& doors);
  ~MapLoader();

  void load_map(const std::string& map_name);
  void add_player(const Ray& position, unsigned int player_id);
  void add_item(const Ray& position, unsigned int resource_id,
                unsigned int item_id);
};

#endif
