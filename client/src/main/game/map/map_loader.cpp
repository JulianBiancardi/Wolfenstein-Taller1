#include "map_loader.h"

#include <yaml-cpp/yaml.h>

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../../common/src/main/ids/map_ids.h"
#include "../entities/object.h"

MapLoader::MapLoader(
    std::vector<std::shared_ptr<Object>>& objects_and_players,
    std::unordered_map<unsigned int, std::shared_ptr<Object>>& objects,
    std::unordered_map<unsigned int, std::shared_ptr<Player>>& players)
    : objects_and_players(objects_and_players),
      objects(objects),
      players(players) {}

MapLoader::~MapLoader() {}

void MapLoader::load_map(const std::string& map_name) {
  YAML::Node yaml_file = YAML::LoadFile("../../res/maps/" + map_name + ".yaml");

  const YAML::Node& objects = yaml_file["objects"];

  YAML::const_iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    const YAML::Node& object = *iter;

    int type = object["type"].as<int>();
    if (type == NULL_TYPE || type == WALLS_TYPE || type == PLAYERS_TYPE) {
      continue;
    }

    int res_id = object["id"].as<int>();
    size_t x = object["x_position"].as<int>();
    size_t y = object["y_position"].as<int>();

    if (type == GUNS_TYPE || type == SOLID_OBJECTS_TYPE ||
        type == NON_SOLID_OBJECTS_TYPE || type == ITEMS_TYPE) {
      add_object(res_id, Point(x + 0.5, y + 0.5));
    }
  }
}

void MapLoader::add_object(unsigned char res_id, Point where) {
  std::shared_ptr<Object> new_object(new Object(res_id, where, 0.0));
  objects.insert(std::make_pair(new_object->get_id(), new_object));
  objects_and_players.push_back(new_object);
}
