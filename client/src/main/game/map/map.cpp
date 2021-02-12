#include "map.h"

#include "../entities/rocket.h"
#include "map_loader.h"

Map::Map(Matrix<int>& map_matrix)
    : BaseMap(map_matrix),
      drawables(),
      ambient_objects(),
      objects(),
      players(),
      loader(drawables, players_shootable, ambient_objects, objects, players) {}

Map::Map(const std::string& map_name)
    : BaseMap(map_name),
      drawables(),
      ambient_objects(),
      objects(),
      players(),
      loader(drawables, players_shootable, ambient_objects, objects, players) {
  loader.load_map(map_name);
}

Map::~Map() {}

void Map::update() {
  std::unordered_map<unsigned int, std::shared_ptr<Player>>::iterator iter;
  for (iter = players.begin(); iter != players.end(); iter++) {
    iter->second->update();
  }
}

void Map::add_item(unsigned int item_id, unsigned char item_type, Point pos) {
  loader.add_item(item_id, item_type, pos);
}

void Map::add_player(unsigned int player_id, const Ray& position) {
  loader.add_player(player_id, position);
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

void Map::shoot_player(unsigned int player_id, unsigned char damage) {
  players.at(player_id)->set_health(
      std::max(0, players.at(player_id)->get_health() - damage));
}

void Map::change_gun(unsigned int player_id, unsigned char gun_id) {
  players.at(player_id)->set_gun(gun_id);
}

void Map::use_bullets(unsigned int player_id, unsigned char gun_id) {
  players.at(player_id)->decrease_bullets(gun_id);
}

void Map::pick_item(unsigned int player_id, unsigned int item_id) {
  Player& player = *(players.at(player_id));
  player.grab_item(*objects.at(item_id));
  objects.erase(item_id);
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

  const Point spawn_point(front_x, front_y);

  std::shared_ptr<Rocket> rocket(new Rocket(spawn_point, angle, rocket_id));
  objects.insert(std::make_pair(rocket_id, std::move(rocket)));
  drawables.push_back(objects.at(rocket_id));
}

void Map::move_rocket(unsigned int rocket_id) {
  ((Rocket*)(objects.at(rocket_id).get()))->move();
}
