#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <string>

#include "map.h"

class MapGenerator {
 private:
 public:
  MapGenerator();

  Map* generate_map(const std::string& file_path);
  void generate_yamlfile(const std::string& file_path, Map* map);

  ~MapGenerator();
};

#endif  // MAP_GENERATOR_H