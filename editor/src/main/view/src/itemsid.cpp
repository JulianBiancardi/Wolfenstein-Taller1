#include "itemsid.h"

#include <string>

#include "iostream"
#include "yaml-cpp/yaml.h"

ItemsId::ItemsId() {
  YAML::Node ids_file = YAML::LoadFile("../../../../common/ids.yaml");

  YAML::const_iterator iter;
  for (iter = ids_file.begin(); iter != ids_file.end(); iter++) {
    size_t id = iter->first.as<size_t>();
    QMap<QString, QString> resources;
    resources.insert("name", iter->second["name"].as<std::string>().c_str());
    resources.insert("icon", iter->second["icon"].as<std::string>().c_str());
    this->ids.insert(id, resources);
  }
}

size_t ItemsId::size() const { return this->ids.size(); }

const QString ItemsId::get_tooltip(size_t id) const {
  return ids.value(id).value("name");
}

const QString ItemsId::get_icon_path(size_t id) const {
  return ids.value(id).value("icon");
}
