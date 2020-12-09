#include "player.h"
#include <cmath>

Player::Player(Point origin, double angle, Map &game_map) :
    shot_bullets(0), points(0), Moveable(origin, angle, game_map, 1),
    Shooter(origin, angle, game_map){
  health = ConfigLoader::player_health;
  bullets = ConfigLoader::player_bullets;
}


Player::Player(double x, double y, double angle, Map &game_map) :
    shot_bullets(0), points(0), Moveable(Point(x, y), angle, game_map, 1),
    Shooter(Point(x, y), angle, game_map){
  health = ConfigLoader::player_health;
  bullets = ConfigLoader::player_bullets;
}

void Player::shoot_player(Player &shot_player, Gun &gun) {
//  shoot_checker();
  int damage_got = gun.shoot(bullets);
  shot_player.receive_damage(damage_got);
}

bool Player::has_bullets(int amount) {
  return (bullets >= amount);
}
/*
void Player::decrease_bullets(int amount) {
  bullets -= amount;
}
*/
void Player::receive_damage(int amount) {
  health -= amount;
}

bool Player::add_gun_if_hasnt(Gun gun) {
  bool found =
      false;//(std::find(guns_bag.begin(), guns_bag.end(), gun) != guns_bag.end());
  if (!found) {
    guns_bag.push_back(gun);
    return true;
  }
  return false;
}

void Player::add_points(int amount) {
  points += amount;
}

void Player::add_health(int amount) {
  health += amount;
}

bool Player::add_health_if_hass_less(int amount, int less_than) {
  if (health < less_than) {
    health += amount;
    return true;
  }
  return false;
}

int Player::get_health() {
  return health;
}
