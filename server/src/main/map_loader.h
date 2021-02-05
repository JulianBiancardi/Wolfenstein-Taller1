#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "../../../common/src/main/object.h"
#include "game/objects/items/item.h"
#include "game/player.h"

class MapLoader {
 private:
  std::unordered_map<unsigned int, Player>& players;
  std::unordered_map<unsigned int, Item*>& items;
  std::unordered_map<unsigned int, Object*>& solid_objects;
  std::vector<Point>& spawn_points;

  void add_spawn_point(const Point& where);
  // static void add_dog(Point& where);
  // static void add_guard(Point& where);
  // static void add_ss(Point& where);
  // static void add_officer(Point& where);
  // static void add_mutant(Point& where);

  void add_machine_gun(const Point& where);
  void add_chain_cannon(const Point& where);
  void add_rocket_launcher(const Point& where);

  void add_food(const Point& where);
  void add_medic_kit(const Point& where);
  void add_blood(const Point& where);
  void add_bullets(const Point& where);
  void add_cross(const Point& where);
  void add_cup(const Point& where);
  void add_chest(const Point& where);
  void add_crown(const Point& where);
  void add_key(const Point& where);

  void add_pillar(const Point& where);
  void add_table(const Point& where);
  void add_barrel(const Point& where);

  void add_normal_door(const Point& where);
  void add_locked_door(const Point& where);

 public:
  MapLoader(std::unordered_map<unsigned int, Player>& players,
            std::unordered_map<unsigned int, Item*>& items,
            std::unordered_map<unsigned int, Object*>& solid_objects,
            std::vector<Point>& spawn_points);
  ~MapLoader();

  void load_map(std::string& map_name);
};

#endif
