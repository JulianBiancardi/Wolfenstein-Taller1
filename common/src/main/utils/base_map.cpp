#include "base_map.h"

#define WALL 1  // TODO Remove this and ask in Config

#include "yaml-cpp/yaml.h"

BaseMap::BaseMap(Matrix<int>& map_matrix) : map_matrix(map_matrix) {}

BaseMap::BaseMap(std::string& map_name) : map_matrix(0, 0) {
  YAML::Node yaml_file = YAML::LoadFile(map_name);
  size_t width = yaml_file["width"].as<int>();
  size_t height = yaml_file["height"].as<int>();
  Matrix<int> map_data(height, width, 0);

  const YAML::Node& objects = yaml_file["objects"];

  YAML::const_iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    const YAML::Node& object = *iter;

    int id = object["id"].as<int>();
    size_t x = object["x_position"].as<int>();
    size_t y = object["y_position"].as<int>();

    map_data(x, y) = id;
  }

  map_matrix = map_data;
}

BaseMap::~BaseMap() {}

const char* BaseMap::get_name() const { return map_name; }

unsigned char BaseMap::get_capacity() const { return player_capacity; }

bool BaseMap::is_wall(size_t x, size_t y) {
  if (map_matrix(x, y) >= WALL) {
    return true;
  }
  return false;
}

int BaseMap::operator()(size_t x, size_t y) { return map_matrix(x, y); }
