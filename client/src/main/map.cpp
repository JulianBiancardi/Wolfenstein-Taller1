#include "map.h"

Map::Map(Matrix<int>& map_matrix) : BaseMap(map_matrix) {}

Map::Map(const std::string& map_name) : BaseMap(map_name) {}

// void Map::add_sprite(Sprite &sprite) { sprites.push_back(sprite); }

Map::~Map() {
  // for (auto object : objects) delete object;
}

void Map::add_player(unsigned int player_id, const Ray& position) {
  std::shared_ptr<Player> player(new Player(position, player_id));
  players.insert(std::make_pair(player_id, std::move(player)));
  objects.push_back((players.at(player_id).get()));
}

const std::vector<Object*>& Map::get_objects() const { return objects; }

const Player& Map::get_player(unsigned int player_id) const {
  return *(players.at(player_id));
}

void Map::move_player(unsigned int player_id, unsigned char direction) {
  players.at(player_id)->move(direction);
}

void Map::rotate_player(unsigned int player_id, unsigned char direction) {
  players.at(player_id)->rotate(direction);
}
