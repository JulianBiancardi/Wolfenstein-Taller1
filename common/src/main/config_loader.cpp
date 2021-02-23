#include "config_loader.h"

#include <iostream>  // TODO DELETE
#include <string>

YAML::Node CL::yaml_file = YAML::LoadFile("../../common/src/main/config.yaml");

std::string CL::sv_host = CL::yaml_file["sv_host"].as<std::string>();
std::string CL::sv_port = CL::yaml_file["sv_port"].as<std::string>();

// Render
int CL::screen_width = CL::yaml_file["screen_width"].as<int>();
int CL::screen_height = CL::yaml_file["screen_height"].as<int>();
bool CL::fullscreen = CL::yaml_file["fullscreen"].as<bool>();
int CL::fps = CL::yaml_file["fps"].as<int>();

// Sound
unsigned int CL::music_volume =
    CL::yaml_file["music_volume"].as<unsigned int>();
unsigned int CL::effect_volume =
    CL::yaml_file["effect_volume"].as<unsigned int>();

// Player
int CL::player_health = CL::yaml_file["player_health"].as<int>();
int CL::player_bullets = CL::yaml_file["player_bullets"].as<int>();
int CL::player_max_bullets = CL::yaml_file["player_max_bullets"].as<int>();
double CL::player_mask_radio = CL::yaml_file["player_mask_radio"].as<double>();
int CL::player_lives = CL::yaml_file["player_lives"].as<int>();
int CL::player_max_points = CL::yaml_file["player_max_points"].as<int>();
int CL::player_respawn_bullets =
    CL::yaml_file["player_respawn_bullets"].as<int>();
double CL::player_speed = CL::yaml_file["player_speed"].as<double>();
double CL::player_rotation_speed =
    CL::yaml_file["player_rotation_speed"].as<double>();
int CL::player_knife_mask_radio =
    CL::yaml_file["player_knife_mask_radio"].as<int>();
double CL::player_ghost_speed =
    CL::yaml_file["player_ghost_speed"].as<double>();

// Bot
int CL::bot_positions_difference_allowed =
    CL::yaml_file["bot_positions_difference_allowed"].as<int>();

// Guns
int CL::bullet_max_dmg = CL::yaml_file["bullet_max_damage"].as<int>();

double CL::knife_range = CL::yaml_file["knife_range"].as<double>();

int CL::pistol_range = CL::yaml_file["pistol_range"].as<int>();
int CL::pistol_bullet_required =
    CL::yaml_file["pistol_bullet_required"].as<int>();
double CL::pistol_spray = CL::yaml_file["pistol_spray"].as<double>();
double CL::pistol_std_dev = CL::yaml_file["pistol_std_dev"].as<double>();

int CL::machine_gun_range = CL::yaml_file["machine_gun_range"].as<int>();
int CL::machine_gun_bullet_required =
    CL::yaml_file["machine_gun_bullet_required"].as<int>();
uint32_t CL::machine_gun_burst_frequency =
    CL::yaml_file["machine_gun_burst_frequency"].as<uint32_t>();
uint32_t CL::machine_gun_shot_frequency =
    CL::yaml_file["machine_gun_shot_frequency"].as<uint32_t>();
double CL::machine_gun_spray = CL::yaml_file["machine_gun_spray"].as<double>();
double CL::machine_gun_std_dev =
    CL::yaml_file["machine_gun_std_dev"].as<double>();

int CL::chain_cannon_range = CL::yaml_file["chain_cannon_range"].as<int>();
int CL::chain_cannon_bullet_required =
    CL::yaml_file["chain_cannon_bullet_required"].as<int>();
uint32_t CL::chain_cannon_frequency =
    CL::yaml_file["chain_cannon_frequency"].as<uint32_t>();
double CL::chain_cannon_spray =
    CL::yaml_file["chain_cannon_spray"].as<double>();
double CL::chain_cannon_std_dev =
    CL::yaml_file["chain_cannon_std_dev"].as<double>();

int CL::rocket_launcher_bullet_required =
    CL::yaml_file["rocket_launcher_bullet_required"].as<int>();

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

int CL::cross_points = CL::yaml_file["cross_points"].as<int>();
int CL::cup_points = CL::yaml_file["cup_points"].as<int>();
int CL::chest_points = CL::yaml_file["chest_points"].as<int>();
int CL::crown_points = CL::yaml_file["crown_points"].as<int>();

// Solid Objects
double CL::pillar_radius = CL::yaml_file["pillar_radius"].as<double>();
double CL::table_width = CL::yaml_file["table_width"].as<double>();
double CL::table_depth = CL::yaml_file["table_depth"].as<double>();
double CL::barrel_radius = CL::yaml_file["barrel_radius"].as<double>();
double CL::rocket_radius = CL::yaml_file["rocket_radius"].as<double>();
double CL::rocket_speed = CL::yaml_file["rocket_speed"].as<double>();
double CL::rocket_explosion_radius =
    CL::yaml_file["rocket_explosion_radius"].as<double>();
double CL::rocket_max_damage = CL::yaml_file["rocket_max_damage"].as<double>();
double CL::rocket_min_damage = CL::yaml_file["rocket_min_damage"].as<double>();

// Other
unsigned int CL::first_id = CL::yaml_file["first_id"].as<unsigned int>();
unsigned int CL::match_length =
    CL::yaml_file["match_length"].as<unsigned int>();
unsigned int CL::door_timer = CL::yaml_file["door_timer"].as<unsigned int>();
double CL::door_speed = CL::yaml_file["door_speed"].as<double>();

ConfigLoader::ConfigLoader() = default;

ConfigLoader::~ConfigLoader() = default;
