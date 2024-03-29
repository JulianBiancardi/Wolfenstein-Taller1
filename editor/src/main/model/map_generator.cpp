#include "include/map_generator.h"

#include <sys/types.h>

#include <fstream>

#include "../../../../common/src/main/ids/map_ids.h"
#include "cell.h"
#include "iostream"
#include "map.h"
#include "map_incorrect_exception.h"
#include "yaml-cpp/yaml.h"

MapGenerator::MapGenerator() {}

Map* MapGenerator::generate_map(const std::string& file_path) {
  YAML::Node file = YAML::LoadFile(file_path);

  size_t rows = file["height"].as<std::size_t>();
  size_t columns = file["width"].as<std::size_t>();

  Map* map = new Map(rows, columns);
  const YAML::Node& objects = file["objects"];
  for (YAML::const_iterator it = objects.begin(); it != objects.end(); ++it) {
    const YAML::Node& object = *it;
    size_t type = object["type"].as<std::size_t>();
    size_t id = object["id"].as<std::size_t>();
    size_t x_pos = object["x_position"].as<std::size_t>();
    size_t y_pos = object["y_position"].as<std::size_t>();
    map->put(y_pos, x_pos, id, type);
  }
  return map;
}

void MapGenerator::generate_yamlfile(const std::string& file_path, Map* map) {
  size_t max_players = 0;

  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "width";
  out << YAML::Value << map->column_count();
  out << YAML::Key << "height";
  out << YAML::Value << map->row_count();
  out << YAML::Key << "objects";
  out << YAML::Value << YAML::BeginSeq;

  for (size_t row = 0; row < map->row_count(); row++) {
    for (size_t column = 0; column < map->column_count(); column++) {
      Cell* celd = map->at(row, column);
      if (celd->get_id() == 0) {
        continue;
      }
      if (celd != NULL) {
        out << YAML::BeginMap;
        out << YAML::Key << "type";
        out << YAML::Value << celd->get_type();
        out << YAML::Key << "id";
        out << YAML::Value << celd->get_id();
        out << YAML::Key << "x_position";
        out << YAML::Value << column;
        out << YAML::Key << "y_position";
        out << YAML::Value << row;
        out << YAML::EndMap;
        if (celd->get_id() == SPAWN_POINT) {
          max_players++;
        }
      }
    }
  }
  out << YAML::EndSeq;
  out << YAML::Key << "max_players";
  out << YAML::Value << max_players;
  out << YAML::EndMap;
  if (max_players == 0) {
    throw MapIncorrectException(
        "The map is incorrect. Remember to add spawns points.");
  }

  std::ofstream fout(file_path);
  fout << out.c_str();
  fout.close();
}

MapGenerator::~MapGenerator() {}