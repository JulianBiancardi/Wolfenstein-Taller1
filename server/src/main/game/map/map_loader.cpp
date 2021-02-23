#include "map_loader.h"

#include <yaml-cpp/yaml.h>

#include "../../../../../common/src/main/ids/map_ids.h"
#include "../objects/circular_object.h"
#include "../objects/door/locked_door.h"
#include "../objects/door/normal_door.h"
#include "../objects/items/blood.h"
#include "../objects/items/bullets.h"
#include "../objects/items/chain_cannon_item.h"
#include "../objects/items/chest.h"
#include "../objects/items/cross.h"
#include "../objects/items/crown.h"
#include "../objects/items/cup.h"
#include "../objects/items/food.h"
#include "../objects/items/key.h"
#include "../objects/items/machine_gun_item.h"
#include "../objects/items/medic_kit.h"
#include "../objects/items/rocket_launcher_item.h"
#include "../objects/rectangular_object.h"

MapLoader::MapLoader(
    unsigned int& next_id, std::unordered_map<unsigned int, Player>& players,
    std::unordered_map<unsigned int, Item*>& items,
    std::unordered_map<unsigned int, Object*>& identifiable_objects,
    std::vector<Object*>& unidentifiable_objects,
    std::vector<Point>& spawn_points, std::vector<Point>& dogs,
    std::unordered_map<std::pair<unsigned int, unsigned int>,
                       std::shared_ptr<Door>, PairHasher>& doors)
    : next_id(next_id),
      door_id(1),
      players(players),
      items(items),
      identifiable_objects(identifiable_objects),
      unidentifiable_objects(unidentifiable_objects),
      spawn_points(spawn_points),
      dogs(dogs),
      doors(doors) {}

MapLoader::~MapLoader() = default;

void MapLoader::load_map(std::string& map_name) {
  YAML::Node yaml_file = YAML::LoadFile("../../res/maps/" + map_name + ".yaml");

  const YAML::Node& objects = yaml_file["objects"];

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
      case DOG:
        add_dog(Point(x, y));
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
      case HORIZONTAL_DOOR:
      case VERTICAL_DOOR:
      case GREY_BRICK_PASSAGE:
      case WOOD_WALL_PASSAGE:
      case GREY_STONE_PASSAGE:
      case BLUE_WALL_PASSAGE:
      case ROCK_WALL_PASSAGE:
        add_normal_door(Point(x, y));
        break;
      case HORIZONTAL_LOCKED_DOOR:
      case VERTICAL_LOCKED_DOOR:
        add_locked_door(Point(x, y));
        break;
    }
  }
}

void MapLoader::add_spawn_point(const Point& where) {
  spawn_points.push_back(where);
}

void MapLoader::add_dog(const Point& where) { dogs.push_back(where); }

void MapLoader::add_machine_gun(const Point& where) {
  auto new_machine_gun = new MachineGunItem(where, next_id);
  items.insert({new_machine_gun->get_id(), new_machine_gun});
  next_id++;
}

void MapLoader::add_chain_cannon(const Point& where) {
  auto new_chain_cannon = new ChainCannonItem(where, next_id);
  items.insert({new_chain_cannon->get_id(), new_chain_cannon});
  next_id++;
}

void MapLoader::add_rocket_launcher(const Point& where) {
  auto new_rocket_launcher = new RocketLauncherItem(where, next_id);
  items.insert({new_rocket_launcher->get_id(), new_rocket_launcher});
  next_id++;
}

void MapLoader::add_food(const Point& where) {
  auto new_food = new Food(where, next_id);
  items.insert({new_food->get_id(), new_food});
  next_id++;
}

void MapLoader::add_medic_kit(const Point& where) {
  auto new_medic_kit = new MedicKit(where, next_id);
  items.insert({new_medic_kit->get_id(), new_medic_kit});
  next_id++;
}

void MapLoader::add_blood(const Point& where) {
  auto new_blood = new Blood(where, next_id);
  items.insert({new_blood->get_id(), new_blood});
  next_id++;
}

void MapLoader::add_bullets(const Point& where) {
  auto new_bullets = new Bullets(where, CL::bullets_amount, next_id);
  items.insert({new_bullets->get_id(), new_bullets});
  next_id++;
}

void MapLoader::add_cross(const Point& where) {
  auto new_cross = new Cross(where, next_id);
  items.insert({new_cross->get_id(), new_cross});
  next_id++;
}

void MapLoader::add_cup(const Point& where) {
  auto new_cup = new Cup(where, next_id);
  items.insert({new_cup->get_id(), new_cup});
  next_id++;
}

void MapLoader::add_chest(const Point& where) {
  auto new_chest = new Chest(where, next_id);
  items.insert({new_chest->get_id(), new_chest});
  next_id++;
}

void MapLoader::add_crown(const Point& where) {
  auto new_crown = new Crown(where, next_id);
  items.insert({new_crown->get_id(), new_crown});
  next_id++;
}

void MapLoader::add_key(const Point& where) {
  auto new_key = new Key(where, next_id);
  items.insert({new_key->get_id(), new_key});
  next_id++;
}

void MapLoader::add_pillar(const Point& where) {
  auto new_pillar = new CircularObject(CL::pillar_radius, where);
  unidentifiable_objects.push_back(new_pillar);
}

void MapLoader::add_table(const Point& where) {
  auto new_table =
      new RectangularObject(CL::table_width, CL::table_depth, where);
  unidentifiable_objects.push_back(new_table);
}

void MapLoader::add_barrel(const Point& where) {
  auto new_barrel = new CircularObject(CL::barrel_radius, where);
  unidentifiable_objects.push_back(new_barrel);
}

void MapLoader::add_normal_door(const Point& where) {
  auto new_door = new NormalDoor(where, door_id++);
  doors.insert(
      std::make_pair(std::make_pair(where.getX(), where.getY()), new_door));
}

void MapLoader::add_locked_door(const Point& where) {
  auto new_door = new LockedDoor(where, door_id++);
  doors.insert(
      std::make_pair(std::make_pair(where.getX(), where.getY()), new_door));
}