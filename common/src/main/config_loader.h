#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <fstream>
#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

class ConfigLoader;
typedef ConfigLoader CL;

class ConfigLoader {
 public:
  ConfigLoader();
  ~ConfigLoader();
  // static ConfigLoader& get_init_configs();

  static YAML::Node yaml_file;

  static std::string sv_host;
  static std::string sv_port;

  static int screen_width;
  static int screen_height;
  static bool fullscreen;
  static int fps;

  static unsigned int music_volume;
  static unsigned int effect_volume;

  static int player_health;
  static int player_bullets;
  static int player_max_bullets;
  static double player_mask_radio;
  static int player_lives;
  static int player_max_points;
  static int player_respawn_bullets;
  static double player_speed;
  static double player_rotation_speed;
  static int player_knife_mask_radio;
  static double player_ghost_speed;

  static int bot_positions_difference_allowed;

  static int bullet_max_dmg;

  static double knife_range;

  static int pistol_range;
  static int pistol_bullet_required;
  static double pistol_spray;
  static double pistol_std_dev;

  static int machine_gun_range;
  static int machine_gun_bullet_required;
  static uint32_t machine_gun_burst_frequency;
  static uint32_t machine_gun_shot_frequency;
  static double machine_gun_spray;
  static double machine_gun_std_dev;

  static int chain_cannon_range;
  static int chain_cannon_bullet_required;
  static uint32_t chain_cannon_frequency;
  static double chain_cannon_spray;
  static double chain_cannon_std_dev;

  static int rocket_launcher_bullet_required;

  static double items_mask_radio;
  static int food_health_recovered;
  static int medic_kit_health_recovered;
  static int blood_health_recovered;
  static int blood_health_recovered_if_less_than;
  static int bullets_amount;
  static int bullets_respawn_amount;
  static double drop_distance_from_dead_player;

  static int cross_points;
  static int cup_points;
  static int chest_points;
  static int crown_points;

  static double pillar_radius;
  static double table_width;
  static double table_depth;
  static double barrel_radius;
  static double rocket_radius;
  static double rocket_speed;
  static double rocket_explosion_radius;
  static double rocket_max_damage;
  static double rocket_min_damage;

  static unsigned int first_id;
  static unsigned int match_length;
  static unsigned int door_timer;
};

#endif
