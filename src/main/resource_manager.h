#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <resource>
#include <unordered_map>

class ResourceManager {
 private:
  std::unordered_map<Resource> resources;

 public:
  ResourceManager();
  ~ResourceManager();
};

ResourceManager::ResourceManager(/* args */) {}

ResourceManager::~ResourceManager() {}

#endif
