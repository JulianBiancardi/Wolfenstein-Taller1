#include "map.h"

#include "../entities/rocket.h"
#include "map_loader.h"

Map::Map(Matrix<int>& map_matrix) : BaseMap(map_matrix) {}

Map::Map(const std::string& map_name) : BaseMap(map_name) {
  MapLoader loader(objects_and_players, objects, players);
  loader.load_map(map_name);
}

Map::~Map() {}

void Map::add_player(unsigned int player_id, const Ray& position) {
  std::shared_ptr<Player> player(new Player(position, player_id));
  players.insert(std::make_pair(player_id, std::move(player)));
  objects_and_players.push_back(players.at(player_id));
}

std::vector<std::shared_ptr<Object>>& Map::get_objects_and_players() {
  return objects_and_players;
}

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
  objects_and_players.erase(
      std::remove(objects_and_players.begin(), objects_and_players.end(),
                  objects.at(item_id)),
      objects_and_players.end());
  objects.erase(item_id);
}

Hit Map::trigger_gun(unsigned int player_id) {
  return std::move(
      players.at(player_id)->trigger_gun(*this, objects_and_players));
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
  objects_and_players.push_back(objects.at(rocket_id));
}

void Map::move_rocket(unsigned int rocket_id) {
  ((Rocket*)(objects.at(rocket_id).get()))->move();
}
