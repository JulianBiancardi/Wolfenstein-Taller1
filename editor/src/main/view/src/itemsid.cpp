#include "itemsid.h"

#include <string>

#include "iostream"
#include "yaml-cpp/yaml.h"

ItemsId::ItemsId() {
  YAML::Node ids_file = YAML::LoadFile("../../../../common/ids.yaml");

  const YAML::Node& ids = ids_file["ids"];
  for (YAML::const_iterator iter = ids.begin(); iter != ids.end(); iter++) {
    const YAML::Node& id = *iter;

    this->ids.insert(id["id"].as<std::size_t>(),
                     id["icon"].as<std::string>().c_str());
  }
}

const QString ItemsId::get_icon_path(size_t id) const { return ids.value(id); }
