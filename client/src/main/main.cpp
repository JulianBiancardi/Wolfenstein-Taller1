#include <syslog.h>

#include <exception>

#include "client.h"

#define ARGS_MIN 3
#define ARGV_HOST 1
#define ARGV_PORT 2

//-----------------------------------------------------
Map load_map();
int main(int argc, char** argv) {
  try {
    if (argc < ARGS_MIN) {
      syslog(LOG_ERR,
             "[Error] - Client Main Thread - Error: amount of arguments is not "
             "enough");
      return EXIT_FAILURE;
    }
    std::string host = argv[ARGV_HOST];
    std::string port = argv[ARGV_PORT];
    Client client(host, port);
    client.run_client();
    return EXIT_SUCCESS;
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] Server Main Thread - Error: %s", e.what());
    return EXIT_FAILURE;
  } catch (...) {
    syslog(LOG_ERR, "[Error] Server Main Thread - Unknown error");
    return EXIT_FAILURE;
  }
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