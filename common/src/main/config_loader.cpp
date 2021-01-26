#include "config_loader.h"

YAML::Node CL::yaml_file = YAML::LoadFile("../../common/src/main/config.yaml");

std::string sv_host = CL::yaml_file["sv_host"].as<std::string>();
std::string sv_port = CL::yaml_file["sv_port"].as<std::string>();

int CL::screen_width = CL::yaml_file["screen_width"].as<int>();
int CL::screen_height = CL::yaml_file["screen_height"].as<int>();

// Player
int CL::player_health = CL::yaml_file["player_health"].as<int>();
int CL::player_bullets = CL::yaml_file["player_bullets"].as<int>();
int CL::player_max_bullets = CL::yaml_file["player_max_bullets"].as<int>();
int CL::player_mask_radio = CL::yaml_file["player_mask_radio"].as<int>();
int CL::player_lives = CL::yaml_file["player_lives"].as<int>();
int CL::player_respawn_bullets =
    CL::yaml_file["player_respawn_bullets"].as<int>();
double CL::player_pace = CL::yaml_file["player_pace"].as<double>();
double CL::player_rotation_angle =
    CL::yaml_file["player_rotation_angle"].as<double>();

// Bot
int CL::bot_positions_difference_allowed =
    CL::yaml_file["bot_positions_difference_allowed"].as<int>();

// Guns
int CL::knife_range = CL::yaml_file["knife_range"].as<int>();

int CL::chain_cannon_bullet_required =
    CL::yaml_file["chain_cannon_bullet_required"].as<int>();
int CL::chain_cannon_base_precision =
    CL::yaml_file["chain_cannon_base_precision"].as<int>();

int CL::pistol_bullet_required =
    CL::yaml_file["pistol_bullet_required"].as<int>();
int CL::pistol_base_precision =
    CL::yaml_file["pistol_base_precision"].as<int>();

int CL::rocket_launcher_bullet_required =
    CL::yaml_file["rocket_launcher_bullet_required"].as<int>();
int CL::rocket_launcher_base_precision =
    CL::yaml_file["rocket_launcher_base_precision"].as<int>();

int CL::machine_gun_bullet_required =
    CL::yaml_file["machine_gun_bullet_required"].as<int>();
int CL::machine_gun_base_precision =
    CL::yaml_file["machine_gun_base_precision"].as<int>();

// Items
double CL::items_mask_radio = CL::yaml_file["items_mask_radio"].as<double>();
int CL::food_health_recovered =
    CL::yaml_file["food_health_recovered"].as<int>();
int CL::medic_kit_health_recovered =
    CL::yaml_file["medic_kit_health_recovered"].as<int>();
int CL::blood_health_recovered =
    CL::yaml_file["blood_health_recovered"].as<int>();
int CL::blood_health_recovered_if_less_than =
    CL::yaml_file["blood_health_recovered_if_less_than"].as<int>();
int CL::bullets_amount = CL::yaml_file["bullets_amount"].as<int>();
int CL::bullets_respawn_amount =
    CL::yaml_file["bullets_respawn_amount"].as<int>();
double CL::drop_distance_from_dead_player =
    CL::yaml_file["drop_distance_from_dead_player"].as<double>();

int CL::crosses_points = CL::yaml_file["crosses_points"].as<int>();
int CL::cup_points = CL::yaml_file["cup_points"].as<int>();
int CL::chests_points = CL::yaml_file["chests_points"].as<int>();
int CL::crown_points = CL::yaml_file["crown_points"].as<int>();

ConfigLoader::ConfigLoader() {
  /*
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
*/
}

ConfigLoader::~ConfigLoader() {}

/*
 ConfigLoader & ConfigLoader::get_init_configs() {
     static ConfigLoader instance;
     return instance;
}
*/