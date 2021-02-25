#include "paths.h"

static const char* asset_prefix = "/var/wolfenstein3D/";

std::string asset_path(const char* relative_path) {
  std::string path;
  path += asset_prefix;
  path += relative_path;
  return path;
}