#include "config_loader.h"

ConfigLoader::ConfigLoader() {
    yaml_file = YAML::LoadFile("../config.yaml");
    //Server Config
    sv_port = this->yaml_file["sv_port"].as<std::string>();

    //Player
    player_health = this->yaml_file["player_health"].as<int>();
    player_bullets = this->yaml_file["player_bullets"].as<int>();

    //Guns
    knife_range = this->yaml_file["knife_range"].as<int>();

    chain_cannon_bullet_required = this->yaml_file
        ["chain_cannon_bullet_required"].as<int>();
    chain_cannon_base_precision = this->yaml_file
        ["chain_cannon_base_precision"].as<int>();

    pistol_bullet_required = this->yaml_file["pistol_bullet_required"].as<int>();
    pistol_base_precision = this->yaml_file["pistol_base_precision"].as<int>();

    rocket_launcher_bullet_required = this->yaml_file
        ["rocket_launcher_bullet_required"].as<int>();
    rocket_launcher_base_precision = this->yaml_file
        ["rocket_launcher_base_precision"].as<int>();

    machine_gun_bullet_required = this->yaml_file
        ["machine_gun_bullet_required"].as<int>();
    machine_gun_base_precision = this->yaml_file
            ["machine_gun_base_precision"].as<int>();

    //Items
    food_health_recovered = this->yaml_file["food_health_recovered"].as<int>();
    medic_kit_health_recovered =
            this->yaml_file["medic_kit_health_recovered"].as<int>();
    blood_health_recovered = this->yaml_file["blood_health_recovered"].as<int>();
    blood_health_recovered_if_less_than =
            this->yaml_file["blood_health_recovered_if_less_than"].as<int>();

    crosses_points = this->yaml_file["crosses_points"].as<int>();
    cup_points = this->yaml_file["cup_points"].as<int>();
    chests_points = this->yaml_file["chests_points"].as<int>();
    crown_points = this->yaml_file["crown_points"].as<int>();

}

 ConfigLoader & ConfigLoader::get_init_configs() {
     static ConfigLoader instance;
     return instance;
}
