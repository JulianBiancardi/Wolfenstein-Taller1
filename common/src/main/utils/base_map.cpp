#include "base_map.h"

#define AIR 0  // TODO Remove this and ask in Config
#include "../ids/map_ids.h"
#include "yaml-cpp/yaml.h"

// TODO Eventually remove
BaseMap::BaseMap(Matrix<int>& map_matrix)
    : map_matrix(map_matrix), player_capacity(10) {}

BaseMap::BaseMap(const std::string& map_name)
    : map_name(map_name), map_matrix(0, 0), player_capacity(0) {
  load_map_matrix();
  load_capacity();
}

BaseMap::~BaseMap() {}

void BaseMap::load_map_matrix() {
  YAML::Node yaml_file = YAML::LoadFile("../../res/maps/" + map_name + ".yaml");
  size_t width = yaml_file["width"].as<int>();
  size_t height = yaml_file["height"].as<int>();
  Matrix<int> map_data(height, width, 0);

  const YAML::Node& objects = yaml_file["objects"];

  YAML::const_iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    const YAML::Node& object = *iter;

    int type = object["type"].as<int>();
    if (type != WALLS_TYPE && type != DOORS_TYPE) {
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
  YAML::Node yaml_file = YAML::LoadFile("../../res/maps/" + map_name + ".yaml");
  player_capacity = yaml_file["max_players"].as<unsigned char>();
}

const std::string& BaseMap::get_name() const { return map_name; }

unsigned char BaseMap::get_capacity() const { return player_capacity; }

bool BaseMap::is_air(size_t x, size_t y) { return map_matrix(x, y) == AIR; }

bool BaseMap::is_wall(size_t x, size_t y) {
  return !is_air(x, y) && !is_door(x, y);
}

bool BaseMap::is_door(size_t x, size_t y) {
  int value = map_matrix(x, y);
  return (value == HORIZONTAL_DOOR || value == VERTICAL_DOOR ||
          value == VERTICAL_LOCKED_DOOR || value == HORIZONTAL_LOCKED_DOOR ||
          value == GREY_BRICK_PASSAGE || value == GREY_STONE_PASSAGE ||
          value == BLUE_WALL_PASSAGE || value == ROCK_WALL_PASSAGE ||
          value == WOOD_WALL_PASSAGE);
}

int BaseMap::operator()(size_t x, size_t y) { return map_matrix(x, y); }

/* Returns the amount of rows in the matrix. */
size_t BaseMap::get_rows() { return map_matrix.get_rows(); }

/* Returns the amount of columns in the matrix. */
size_t BaseMap::get_columns() { return map_matrix.get_columns(); }
