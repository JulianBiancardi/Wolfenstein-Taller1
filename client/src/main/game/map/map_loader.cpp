#include "map_loader.h"

#include <yaml-cpp/yaml.h>

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../../common/src/main/ids/map_ids.h"
#include "../entities/identifiable_object.h"
#include "../entities/object.h"

MapLoader::MapLoader(
    std::vector<std::weak_ptr<Object>>& drawables,
    std::vector<std::weak_ptr<IdentifiableObject>>& players_shootable,
    std::vector<std::shared_ptr<Object>>& ambient_objects,
    std::unordered_map<unsigned int, std::shared_ptr<Object>>& objects,
    std::unordered_map<unsigned int, std::shared_ptr<Player>>& players)
    : drawables(drawables),
      players_shootable(players_shootable),
      ambient_objects(ambient_objects),
      objects(objects),
      players(players) {}

MapLoader::~MapLoader() {}

void MapLoader::add_player(const Ray& position, unsigned int player_id) {
  std::shared_ptr<Player> new_player(new Player(position, player_id));
  players.insert(std::make_pair(player_id, new_player));
  players_shootable.push_back(new_player);
  drawables.push_back(new_player);
}

void MapLoader::add_item(const Ray& position, unsigned int item_id,
                         unsigned char map_id) {
  std::shared_ptr<IdentifiableObject> new_object(
      new IdentifiableObject(position, item_id));
  objects.insert(std::make_pair(new_object->get_id(), new_object));
  drawables.push_back(new_object);
}

void MapLoader::load_map(const std::string& map_name) {
  YAML::Node yaml_file = YAML::LoadFile("../../res/maps/" + map_name + ".yaml");

  const YAML::Node& objects = yaml_file["objects"];

  YAML::const_iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    const YAML::Node& object = *iter;

    int type = object["type"].as<int>();
    if (!(type == SOLID_OBJECTS_TYPE || type == NON_SOLID_OBJECTS_TYPE)) {
      continue;
    }

    int res_id = object["id"].as<int>();
    size_t x = object["x_position"].as<int>();
    size_t y = object["y_position"].as<int>();
    Ray position(x + 0.5, y + 0.5, 0.0);

    add_object(position);
  }
}

void MapLoader::add_object(Ray& position) {
  std::shared_ptr<Object> new_object(new Object(position));
  std::weak_ptr<Object> object_weak_ptr(new_object);
  ambient_objects.push_back(new_object);
  drawables.push_back(object_weak_ptr);
}
