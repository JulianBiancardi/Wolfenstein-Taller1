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

        int knife_range;
        int chain_cannon_bullet_required;
        int chain_cannon_base_precision;
        int pistol_bullet_required;
        int pistol_base_precision;
        int rocket_launcher_bullet_required;
        int rocket_launcher_base_precision;
        int machine_gun_bullet_required;
        int machine_gun_base_precision;

        int food_health_recovered;
        int medic_kit_health_recovered;
        int blood_health_recovered;
        int blood_health_recovered_if_less_than;
        int crosses_points;
        int cup_points;
        int chests_points;
        int crown_points;
};
#endif //WOLFENSTEIN_TALLER1_CONFIG_LOADER_H
