#include "config_loader.h"

#include <string>

YAML::Node CL::yaml_file = YAML::LoadFile("../../common/src/main/config.yaml");

std::string CL::sv_host = CL::yaml_file["sv_host"].as<std::string>();
std::string CL::sv_port = CL::yaml_file["sv_port"].as<std::string>();

int CL::screen_width = CL::yaml_file["screen_width"].as<int>();
int CL::screen_height = CL::yaml_file["screen_height"].as<int>();

// Player
int CL::player_health = CL::yaml_file["player_health"].as<int>();
int CL::player_bullets = CL::yaml_file["player_bullets"].as<int>();
int CL::player_max_bullets = CL::yaml_file["player_max_bullets"].as<int>();
double CL::player_mask_radio = CL::yaml_file["player_mask_radio"].as<double>();
int CL::player_lives = CL::yaml_file["player_lives"].as<int>();
int CL::player_respawn_bullets =
    CL::yaml_file["player_respawn_bullets"].as<int>();
double CL::player_speed = CL::yaml_file["player_speed"].as<double>();
double CL::player_rotation_speed =
    CL::yaml_file["player_rotation_speed"].as<double>();
int CL::player_knife_mask_radio =
    CL::yaml_file["player_knife_mask_radio"].as<int>();

// Bot
int CL::bot_positions_difference_allowed =
    CL::yaml_file["bot_positions_difference_allowed"].as<int>();

// Guns
int CL::chain_cannon_bullet_required =
    CL::yaml_file["chain_cannon_bullet_required"].as<int>();

int CL::pistol_bullet_required =
    CL::yaml_file["pistol_bullet_required"].as<int>();

int CL::rocket_launcher_bullet_required =
    CL::yaml_file["rocket_launcher_bullet_required"].as<int>();

int CL::machine_gun_bullet_required =
    CL::yaml_file["machine_gun_bullet_required"].as<int>();

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

// Solid Objects
double CL::pillar_radius = CL::yaml_file["pillar_radius"].as<double>();
double CL::table_width = CL::yaml_file["table_width"].as<double>();
double CL::table_depth = CL::yaml_file["table_depth"].as<double>();
double CL::barrel_radius = CL::yaml_file["barrel_radius"].as<double>();
double CL::rocket_radius = CL::yaml_file["rocket_radius"].as<double>();
double CL::rocket_speed = CL::yaml_file["rocket_speed"].as<double>();

// Other
unsigned int CL::match_length =
    CL::yaml_file["match_length"].as<unsigned int>();
unsigned int CL::door_timer = CL::yaml_file["door_timer"].as<unsigned int>();

ConfigLoader::ConfigLoader() = default;

ConfigLoader::~ConfigLoader() = default;
