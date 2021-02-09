#include "map.h"

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

Hit Map::trigger_gun(unsigned int player_id) {
  return std::move(
      players.at(player_id)->trigger_gun(*this, objects_and_players));
}

void Map::untrigger_gun(unsigned int player_id) {
  players.at(player_id)->untrigger_gun();
}