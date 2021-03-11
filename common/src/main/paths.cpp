#include "paths.h"

static const char* asset_prefix = "/var/wolfenstein3D/";
static const char* config_prefix = "/etc/wolfenstein3D/";

std::string asset_path(const char* relative_path) {
  std::string path;
  path += asset_prefix;
  path += relative_path;
  return path;
}

std::string config_path(const char* relative_path) {
  std::string path;
  path += config_prefix;
  path += relative_path;
  return path;
}