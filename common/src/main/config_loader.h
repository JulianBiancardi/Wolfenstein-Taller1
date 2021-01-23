#ifndef WOLFENSTEIN_TALLER1_CONFIG_LOADER_H
#define WOLFENSTEIN_TALLER1_CONFIG_LOADER_H

#include <fstream>
#include <iostream>

#include "yaml-cpp/yaml.h"

class ConfigLoader;
typedef ConfigLoader CL;

class ConfigLoader {
 public:
  ConfigLoader();
  // static ConfigLoader& get_init_configs();

  static YAML::Node yaml_file;

  static std::string sv_port;

  static int player_health;
  static int player_bullets;
  static int player_max_bullets;
  static int player_mask_radio;
  static int player_lives;
  static int player_respawn_bullets;
  static double player_pace;
  static double player_rotation_angle;

  static int knife_range;
  static int chain_cannon_bullet_required;
  static int chain_cannon_base_precision;
  static int pistol_bullet_required;
  static int pistol_base_precision;
  static int rocket_launcher_bullet_required;
  static int rocket_launcher_base_precision;
  static int machine_gun_bullet_required;
  static int machine_gun_base_precision;

  static double items_mask_radio;
  static int food_health_recovered;
  static int medic_kit_health_recovered;
  static int blood_health_recovered;
  static int blood_health_recovered_if_less_than;
  static int bullets_amount;
  static int bullets_respawn_amount;
  static double drop_distance_from_dead_player;

  static int crosses_points;
  static int cup_points;
  static int chests_points;
  static int crown_points;
};

#endif  // WOLFENSTEIN_TALLER1_CONFIG_LOADER_H
