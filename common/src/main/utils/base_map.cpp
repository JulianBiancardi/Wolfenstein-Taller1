#include "base_map.h"

#define WALL 1  // TODO Remove this and ask in Config

#include "yaml-cpp/yaml.h"

// TODO Eventually remove
BaseMap::BaseMap(Matrix<int>& map_matrix)
    : map_matrix(map_matrix), player_capacity(10) {}

BaseMap::BaseMap(std::string& map_name)
    : map_name(map_name), map_matrix(0, 0), player_capacity(5) {}

BaseMap::~BaseMap() {}

void BaseMap::load_map_matrix() {
  YAML::Node yaml_file =
      YAML::LoadFile("../../../res/maps/" + map_name + ".yaml");
  size_t width = yaml_file["width"].as<int>();
  size_t height = yaml_file["height"].as<int>();
  Matrix<int> map_data(height, width, 0);

  const YAML::Node& objects = yaml_file["objects"];

  YAML::const_iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    const YAML::Node& object = *iter;

    int type = object["type"].as<int>();
    if (type > 0) {
      continue;
    }

    int id = object["id"].as<int>();
    size_t x = object["x_position"].as<int>();
    size_t y = object["y_position"].as<int>();

    map_data(x, y) = id;
  }

  map_matrix = map_data;
}

void BaseMap::load_capacity() {
  YAML::Node yaml_file = YAML::LoadFile(map_name);
  player_capacity = yaml_file["max_players"].as<unsigned char>();
}

const std::string& BaseMap::get_name() const { return map_name; }

unsigned char BaseMap::get_capacity() const { return player_capacity; }

bool BaseMap::is_wall(size_t x, size_t y) {
  if (map_matrix(x, y) >= WALL) {
    return true;
  }
  return false;
}

int BaseMap::operator()(size_t x, size_t y) { return map_matrix(x, y); }
