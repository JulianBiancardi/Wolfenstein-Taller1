#include "map.h"

#include "map_loader.h"

Map::Map(Matrix<int>& map_matrix)
    : BaseMap(map_matrix),
      drawables(),
      ambient_objects(),
      items(),
      players(),
      loader(drawables, players_shootable, ambient_objects, items, players) {}

Map::Map(const std::string& map_name)
    : BaseMap(map_name),
      drawables(),
      ambient_objects(),
      items(),
      players(),
      loader(drawables, players_shootable, ambient_objects, items, players) {
  loader.load_map(map_name);
}

Map::~Map() {}

void Map::update() {
  std::unordered_map<unsigned int, std::shared_ptr<Player>>::iterator iter;
  for (iter = players.begin(); iter != players.end(); iter++) {
    iter->second->update();
  }
}

void Map::add_item(unsigned int item_id, const Ray& position,
                   unsigned char item_type) {
  loader.add_item(position, item_type, item_id);
}

void Map::add_player(unsigned int player_id, const Ray& position) {
  loader.add_player(position, player_id);
}

std::vector<std::weak_ptr<Object>>& Map::get_drawables() { return drawables; }

const Player& Map::get_player(unsigned int player_id) const {
  return *(players.at(player_id));
}

void Map::move_player(unsigned int player_id, unsigned char direction) {
  players.at(player_id)->move(direction);
}

void Map::rotate_player(unsigned int player_id, unsigned char direction) {
  players.at(player_id)->rotate(direction);
}

void Map::shoot_player(unsigned int player_id, unsigned char damage,
                       unsigned int damager_id) {
  auto player = players.at(player_id);
  auto damager = players.at(damager_id);

  player->decrease_health(damage);

  if (player->is_dead()) {
    damager->add_kill();
    if (player->has_lives_left()) {
      player->respawn();
      // TODO Add items
    } else {
      // TODO Ghost mode?
    }
  }
}

void Map::change_gun(unsigned int player_id, unsigned char gun_id) {
  players.at(player_id)->set_gun(gun_id);
}

void Map::use_bullets(unsigned int player_id, unsigned char gun_id) {
  players.at(player_id)->decrease_bullets(gun_id);
}

int Map::pick_item(unsigned int player_id, unsigned int item_id) {
  Player& player = *(players.at(player_id));
  std::shared_ptr<Item> item = items.at(item_id);
  int res_id = item->get_res_id();
  item->use_on(player);
  items.erase(item_id);
  return res_id;
}

Hit Map::trigger_gun(unsigned int player_id) {
  return std::move(
      players.at(player_id)->trigger_gun(*this, players_shootable));
}

void Map::untrigger_gun(unsigned int player_id) {
  players.at(player_id)->untrigger_gun();
}

void Map::shoot_rocket(unsigned int player_id, unsigned int rocket_id) {
  const Point& player_position = players.at(player_id)->get_position();
  double angle = players.at(player_id)->get_angle();

  double front_x = player_position.getX() + cos(angle) * CL::player_mask_radio;
  double front_y = player_position.getY() - sin(angle) * CL::player_mask_radio;

  Ray spawn_point(front_x, front_y, 0.0);

  std::shared_ptr<Rocket> rocket =
      std::make_shared<Rocket>(spawn_point, rocket_id, player_id);
  rockets.insert(std::make_pair(rocket_id, rocket));
  drawables.push_back(rocket);
}

void Map::move_rocket(unsigned int rocket_id) { rockets.at(rocket_id)->move(); }

unsigned int Map::get_rocket_owner_id(unsigned int rocket_id) {
  return rockets.at(rocket_id)->get_owner_id();
}
