#include <exception>

#include "../../../common/src/main/constants.h"
#include "client.h"
#include "iostream"
#include "map.h"
#include "yaml-cpp/yaml.h"

//-----------------------------------------------------
Map load_map();
int main() {
  try {
    std::cout << "Starting" << std::endl;
    Map map = load_map();
    Client client(map);
    client.launch();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return ERROR;
  }
  return NO_ERROR;  // TODO Change name to SUCCED
}

// TODO Move to MapReader
Map load_map() {
  YAML::Node yaml_file = YAML::LoadFile("../../editor/src/main/build/new_map.yaml");
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

  return Map(map_data);
}