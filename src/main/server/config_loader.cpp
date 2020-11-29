#include "config_loader.h"

ConfigLoader::ConfigLoader() {
    yaml_file = YAML::LoadFile("../config.yaml");
    sv_port = this->yaml_file["sv_port"].as<std::string>();
}

 ConfigLoader & ConfigLoader::get_init_configs() {
     static ConfigLoader instance;
     return instance;
}
