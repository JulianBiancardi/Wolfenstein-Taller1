#include "map_loader.h"

#include <yaml-cpp/yaml.h>

#include <utility>

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../../common/src/main/ids/map_ids.h"
#include "../../../../../common/src/main/paths.h"
#include "../entities/doors/horizontal_door.h"
#include "../entities/doors/passage.h"
#include "../entities/doors/vertical_door.h"
#include "../entities/identifiable_object.h"
#include "../entities/items/blood.h"
#include "../entities/items/bullets.h"
#include "../entities/items/chain_cannon_item.h"
#include "../entities/items/chest.h"
#include "../entities/items/cross.h"
#include "../entities/items/crown.h"
#include "../entities/items/cup.h"
#include "../entities/items/food.h"
#include "../entities/items/key.h"
#include "../entities/items/machine_gun_item.h"
#include "../entities/items/medkit.h"
#include "../entities/items/rocket_launcher_item.h"

MapLoader::MapLoader(
    std::vector<std::weak_ptr<Object>>& drawables,
    std::vector<std::weak_ptr<IdentifiableObject>>& players_shootable,
    std::vector<std::shared_ptr<Object>>& ambient_objects,
    std::unordered_map<unsigned int, std::shared_ptr<Item>>& items,
    std::unordered_map<unsigned int, std::shared_ptr<Player>>& players,
    std::unordered_map<std::pair<unsigned int, unsigned int>,
                       std::unique_ptr<BaseDoor>, PairHasher>& doors,
    std::unordered_map<unsigned int, std::shared_ptr<Rocket>>& rockets)
    : next_id(CL::first_id),
      drawables(drawables),
      players_shootable(players_shootable),
      ambient_objects(ambient_objects),
      items(items),
      players(players),
      doors(doors),
      rockets(rockets) {}

MapLoader::~MapLoader() {}

void MapLoader::add_player(const Ray& position, unsigned int player_id) {
  std::shared_ptr<Player> new_player =
      std::make_shared<Player>(position, player_id);
  std::weak_ptr<Object> player_weak_ptr(new_player);
  std::weak_ptr<IdentifiableObject> player_id_weak_ptr(new_player);
  players.insert(std::make_pair(player_id, std::move(new_player)));
  players_shootable.push_back(player_id_weak_ptr);
  drawables.push_back(player_weak_ptr);
}

void MapLoader::add_item(const Ray& position, unsigned int resource_id) {
  std::shared_ptr<Item> new_item;
  switch (resource_id) {
    case MACHINE_GUN:
      new_item =
          std::make_shared<MachineGunItem>(position, resource_id, next_id++);
      break;
    case CHAIN_CANNON:
      new_item =
          std::make_shared<ChainCannonItem>(position, resource_id, next_id++);
      break;
    case ROCKET_LAUNCHER:
      new_item = std::make_shared<RocketLauncherItem>(position, resource_id,
                                                      next_id++);
      break;
    case FOOD:
      new_item = std::make_shared<Food>(position, resource_id, next_id++);
      break;
    case MEDKIT:
      new_item = std::make_shared<Medkit>(position, resource_id, next_id++);
      break;
    case BLOOD:
      new_item = std::make_shared<Blood>(position, resource_id, next_id++);
      break;
    case BULLETS:
      new_item = std::make_shared<Bullets>(position, resource_id, next_id++);
      break;
    case CROSS:
      new_item = std::make_shared<Cross>(position, resource_id, next_id++);
      break;
    case CUP:
      new_item = std::make_shared<Cup>(position, resource_id, next_id++);
      break;
    case CHEST:
      new_item = std::make_shared<Chest>(position, resource_id, next_id++);
      break;
    case CROWN:
      new_item = std::make_shared<Crown>(position, resource_id, next_id++);
      break;
    case KEY:
      new_item = std::make_shared<Key>(position, resource_id, next_id++);
      break;
  }
  std::weak_ptr<Object> item_weak_ptr(new_item);
  items.insert(std::make_pair(new_item->get_id(), std::move(new_item)));
  drawables.push_back(item_weak_ptr);
}

void MapLoader::load_map(const std::string& map_name) {
  YAML::Node yaml_file =
      YAML::LoadFile(asset_path("/res/maps/") + map_name + ".yaml");

  const YAML::Node& objects = yaml_file["objects"];

  YAML::const_iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    const YAML::Node& object = *iter;

    int type = object["type"].as<int>();
    int resource_id = object["id"].as<int>();
    double x = object["x_position"].as<int>() + 0.5;
    double y = object["y_position"].as<int>() + 0.5;

    if (type == DOORS_TYPE) {
      add_door(x, y, resource_id);
    } else if (type == GUNS_TYPE || type == ITEMS_TYPE) {
      add_item(Ray(x, y, 0.0), resource_id);
    } else if (type == SOLID_OBJECTS_TYPE || type == NON_SOLID_OBJECTS_TYPE) {
      add_object(Ray(x, y, 0.0), resource_id);
    }
  }
}

void MapLoader::add_object(const Ray& position, unsigned int resource_id) {
  std::shared_ptr<Object> new_object =
      std::make_shared<Object>(position, resource_id);
  std::weak_ptr<Object> object_weak_ptr(new_object);
  ambient_objects.push_back(new_object);
  drawables.push_back(object_weak_ptr);
}

void MapLoader::add_door(unsigned int x, unsigned int y,
                         unsigned int resource_id) {
  if (resource_id == HORIZONTAL_DOOR || resource_id == HORIZONTAL_LOCKED_DOOR) {
    std::unique_ptr<BaseDoor> door(new HorizontalDoor(x, y, resource_id));
    std::pair<unsigned int, unsigned int> key(x, y);
    doors.insert(std::make_pair(key, std::move(door)));
  } else if (resource_id == VERTICAL_DOOR ||
             resource_id == VERTICAL_LOCKED_DOOR) {
    std::unique_ptr<BaseDoor> door(new VerticalDoor(x, y, resource_id));
    std::pair<unsigned int, unsigned int> key(x, y);
    doors.insert(std::make_pair(key, std::move(door)));
  } else {
    std::unique_ptr<BaseDoor> door(new Passage(x, y, resource_id));
    std::pair<unsigned int, unsigned int> key(x, y);
    doors.insert(std::make_pair(key, std::move(door)));
  }
}

void MapLoader::add_rocket(const Ray& position, unsigned int player_id) {
  std::shared_ptr<Rocket> rocket =
      std::make_shared<Rocket>(position, next_id++, player_id);
  rockets.insert(std::make_pair(rocket->get_id(), rocket));
  drawables.push_back(rocket);
}
