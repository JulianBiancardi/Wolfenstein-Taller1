#ifndef WOLFENSTEIN_TALLER1_CONFIG_LOADER_H
#define WOLFENSTEIN_TALLER1_CONFIG_LOADER_H
#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"

class ConfigLoader {
    public:

    ConfigLoader();
    static ConfigLoader& get_init_configs();

    YAML::Node yaml_file;
    std::string sv_port;
};
#endif //WOLFENSTEIN_TALLER1_CONFIG_LOADER_H
