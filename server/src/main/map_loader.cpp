#include "map_loader.h"

#include <yaml-cpp/yaml.h>

#include "../../../common/src/main/config_loader.h"
#include "../../../common/src/main/ids/map_ids.h"
#include "game/objects/circular_object.h"
#include "game/objects/door/locked_door.h"
#include "game/objects/door/normal_door.h"
#include "game/objects/items/blood.h"
#include "game/objects/items/bullets.h"
#include "game/objects/items/chain_cannon_item.h"
#include "game/objects/items/chest.h"
#include "game/objects/items/cross.h"
#include "game/objects/items/crown.h"
#include "game/objects/items/cup.h"
#include "game/objects/items/food.h"
#include "game/objects/items/key.h"
#include "game/objects/items/machine_gun_item.h"
#include "game/objects/items/medic_kit.h"
#include "game/objects/items/rocket_launcher_item.h"
#include "game/objects/rectangular_object.h"

MapLoader::MapLoader(std::unordered_map<unsigned int, Player>& players,
                     std::unordered_map<unsigned int, Item*>& items,
                     std::unordered_map<unsigned int, Object*>& solid_objects,
                     std::vector<Point>& spawn_points)
    : players(players),
      items(items),
      solid_objects(solid_objects),
      spawn_points(spawn_points) {}

MapLoader::~MapLoader() {}

void MapLoader::load_map(std::string& map_name) {
  YAML::Node yaml_file = YAML::LoadFile("../../res/maps/" + map_name + ".yaml");

  const YAML::Node& objects = yaml_file["objects"];

  unsigned int id_counter = 1;
  YAML::const_iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    const YAML::Node& object = *iter;

    int type = object["type"].as<int>();
    if (type == NULL_TYPE || type == WALLS_TYPE) {
      continue;
    }

    int id = object["id"].as<int>();
    double x = object["x_position"].as<int>() + 0.5;
    double y = object["y_position"].as<int>() + 0.5;

    switch (id) {
      case SPAWN_POINT:
        add_spawn_point(Point(x, y));
        break;
      case MACHINE_GUN:
        add_machine_gun(Point(x, y));
        break;
      case CHAIN_CANNON:
        add_chain_cannon(Point(x, y));
        break;
      case ROCKET_LAUNCHER:
        add_rocket_launcher(Point(x, y));
        break;
      case FOOD:
        add_food(Point(x, y));
        break;
      case MEDKIT:
        add_medic_kit(Point(x, y));
        break;
      case BLOOD:
        add_blood(Point(x, y));
        break;
      case BULLETS:
        add_bullets(Point(x, y));
        break;
      case CROSS:
        add_cross(Point(x, y));
        break;
      case CUP:
        add_cup(Point(x, y));
        break;
      case CHEST:
        add_chest(Point(x, y));
        break;
      case CROWN:
        add_crown(Point(x, y));
        break;
      case KEY:
        add_key(Point(x, y));
        break;
      case PILLAR:
        // TODO Change to add round and add square
        add_pillar(Point(x, y));
        break;
      case LARGE_TABLE:
        add_table(Point(x, y));
        break;
      case ROUND_TABLE:
        add_barrel(Point(x, y));
        break;
      case BARREL:
        add_barrel(Point(x, y));
        break;
      case DOOR:
        add_normal_door(Point(x, y));
        break;
      case LOCKED_DOOR:
        add_locked_door(Point(x, y));
        break;
    }

    if (type == NON_SOLID_OBJECTS_TYPE) {
      Identifiable::increase_id();
    }
  }
}

void MapLoader::add_spawn_point(const Point& where) {
  spawn_points.push_back(where);
}

void MapLoader::add_machine_gun(const Point& where) {
  MachineGunItem* new_machine_gun = new MachineGunItem(where);
  items.insert({new_machine_gun->get_id(), new_machine_gun});
}

void MapLoader::add_chain_cannon(const Point& where) {
  ChainCannonItem* new_chain_cannon = new ChainCannonItem(where);
  items.insert({new_chain_cannon->get_id(), new_chain_cannon});
}

void MapLoader::add_rocket_launcher(const Point& where) {
  RocketLauncherItem* new_rocket_launcher = new RocketLauncherItem(where);
  items.insert({new_rocket_launcher->get_id(), new_rocket_launcher});
}

void MapLoader::add_food(const Point& where) {
  Food* new_food = new Food(where);
  items.insert({new_food->get_id(), new_food});
}

void MapLoader::add_medic_kit(const Point& where) {
  MedicKit* new_medic_kit = new MedicKit(where);
  items.insert({new_medic_kit->get_id(), new_medic_kit});
}

void MapLoader::add_blood(const Point& where) {
  Blood* new_blood = new Blood(where);
  items.insert({new_blood->get_id(), new_blood});
}

void MapLoader::add_bullets(const Point& where) {
  Bullets* new_bullets = new Bullets(where, CL::bullets_amount);
  items.insert({new_bullets->get_id(), new_bullets});
}

void MapLoader::add_cross(const Point& where) {
  Cross* new_cross = new Cross(where);
  items.insert({new_cross->get_id(), new_cross});
}

void MapLoader::add_cup(const Point& where) {
  Cup* new_cup = new Cup(where);
  items.insert({new_cup->get_id(), new_cup});
}

void MapLoader::add_chest(const Point& where) {
  Chest* new_chest = new Chest(where);
  items.insert({new_chest->get_id(), new_chest});
}

void MapLoader::add_crown(const Point& where) {
  Crown* new_crown = new Crown(where);
  items.insert({new_crown->get_id(), new_crown});
}

void MapLoader::add_key(const Point& where) {
  Key* new_key = new Key(where);
  items.insert({new_key->get_id(), new_key});
}

void MapLoader::add_pillar(const Point& where) {
  CircularObject* new_pillar = new CircularObject(CL::pillar_radius, where);
  solid_objects.insert({new_pillar->get_id(), new_pillar});
}

void MapLoader::add_table(const Point& where) {
  RectangularObject* new_table =
      new RectangularObject(CL::table_width, CL::table_depth, where);
  solid_objects.insert({new_table->get_id(), new_table});
}

void MapLoader::add_barrel(const Point& where) {
  CircularObject* new_barrel = new CircularObject(CL::barrel_radius, where);
  solid_objects.insert({new_barrel->get_id(), new_barrel});
}

void MapLoader::add_normal_door(const Point& where) {
  NormalDoor* new_door = new NormalDoor(where);
  solid_objects.insert({new_door->get_id(), new_door});
}

void MapLoader::add_locked_door(const Point& where) {
  LockedDoor* new_door = new LockedDoor(where);
  solid_objects.insert({new_door->get_id(), new_door});
}
