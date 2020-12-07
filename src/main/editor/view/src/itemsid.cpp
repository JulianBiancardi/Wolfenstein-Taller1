#include "itemsid.h"

#include <string>

#include "iostream"
#include "yaml-cpp/yaml.h"

ItemsId::ItemsId() {
  YAML::Node file = YAML::LoadFile("../../ids.yaml");

  const YAML::Node& ids = file["ids"];
  for (YAML::const_iterator it = ids.begin(); it != ids.end(); ++it) {
    const YAML::Node& id = *it;

    this->ids.insert(id["id"].as<std::size_t>(),
                     id["icon"].as<std::string>().c_str());
  }
}

const QString ItemsId::get_icon_path(size_t id) const { return ids.value(id); }
