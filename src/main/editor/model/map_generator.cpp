#include "map_generator.h"

#include <sys/types.h>

#include <fstream>

#include "celd.h"
#include "iostream"
#include "map.h"
#include "yaml-cpp/yaml.h"

MapGenerator::MapGenerator() {}

void MapGenerator::generate_map(const std::string& file_path) {
  YAML::Node file = YAML::LoadFile(file_path);

  size_t width = file["width"].as<std::size_t>();
  size_t height = file["height"].as<std::size_t>();
  Map map(height, width);
  const YAML::Node& objects = file["objects"];
  for (YAML::const_iterator it = objects.begin(); it != objects.end(); ++it) {
    const YAML::Node& object = *it;
    size_t id = object["id"].as<std::size_t>();
    size_t x_pos = object["x_position"].as<std::size_t>();
    size_t y_pos = object["y_position"].as<std::size_t>();
    map.put(y_pos, x_pos, id);
  }
  map.print();
}

void MapGenerator::generate_yamlfile(Map* map) {
  std::cout << "generating file" << std::endl;
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
      Celd* celd = map->at(row, column);
      if (celd != NULL) {
        out << YAML::BeginMap;
        out << YAML::Key << "id";
        out << YAML::Value << celd->get_id();
        out << YAML::Key << "x_position";
        out << YAML::Value << column;
        out << YAML::Key << "y_position";
        out << YAML::Value << row;
        out << YAML::EndMap;
      }
    }
  }
  out << YAML::EndSeq;
  out << YAML::EndMap;
  std::ofstream fout("new_map.yaml");
  fout << out.c_str();
}

MapGenerator::~MapGenerator() {}