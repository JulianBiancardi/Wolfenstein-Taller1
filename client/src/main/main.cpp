#include <exception>

#include "client.h"
#include "iostream"
#include "map.h"
#include "yaml-cpp/yaml.h"

#define ARGS_MIN 3
#define ARGV_HOST 1
#define ARGV_PORT 2

//-----------------------------------------------------
Map load_map();
int main(int argc, char** argv) {
  if (argc < ARGS_MIN) {
    std::cout << "Error: el comando que ha ingresado no se reconoce. Quizas "
                 "quiso decir: ./client host port"
              << std::endl;
    return EXIT_FAILURE;
  }

  try {
    std::cout << "Starting" << std::endl;
    std::string host = argv[ARGV_HOST];
    std::string port = argv[ARGV_PORT];
    Map map = load_map();
    Client client(host, port, map);
    client.launch();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

// TODO Move to MapReader
Map load_map() {
  YAML::Node yaml_file =
      YAML::LoadFile("../../editor/src/main/build/new_map.yaml");
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