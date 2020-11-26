#ifndef WOLFENSTEIN_TALLER1_CONFIG_LOADER_H
#define WOLFENSTEIN_TALLER1_CONFIG_LOADER_H
#include <iostream>
#include <fstream>
#include "json.hpp"

class ConfigLoader {
    public:
        nlohmann::json json_file;

        ConfigLoader();

        std::string sv_port;

        static ConfigLoader& get_init_configs();
};
#endif //WOLFENSTEIN_TALLER1_CONFIG_LOADER_H
