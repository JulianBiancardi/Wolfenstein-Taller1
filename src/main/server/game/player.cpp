#include "player.h"
#include <cmath>

Player::Player(Point origin, double angle, Map &game_map) :
    angled_position(origin, angle), shot_bullets(0), points(0), map(game_map) {
  health = ConfigLoader::player_health;
  //health = 100;
  bullets = ConfigLoader::player_bullets;
  //bullets = 8;
  pace = 1;
}

Player::Player(int x, int y, double angle, Map &game_map) :
    angled_position(x, y, angle), shot_bullets(0), points(0), map(game_map) {
  health = ConfigLoader::player_health;
  //health = 100;
  bullets = ConfigLoader::player_bullets;
  //bullets = 8;
  pace = 1;
}

void Player::move_from_current_position_if_can(double direction_angle) {
  double next_x = angled_position.get_origin().getX() +
      cos(angled_position.get_angle() + direction_angle) * pace;
  double next_y = angled_position.get_origin().getY() +
      sin(angled_position.get_angle() + direction_angle) * pace;
  if (!map.is_wall(next_x, next_y))
    angled_position.set_origin(next_x, next_y);
}

void Player::move_up() {
  move_from_current_position_if_can(0);
}

void Player::move_down() {
  move_from_current_position_if_can(M_PI);
}

void Player::move_right() {
  move_from_current_position_if_can(3 * M_PI / 2);
}

void Player::move_left() {
  move_from_current_position_if_can(M_PI / 2);
}

void Player::move_up_right() {
  move_from_current_position_if_can(7 * M_PI / 4);
}

void Player::move_up_left() {
  move_from_current_position_if_can(M_PI / 4);
}

void Player::move_down_right() {
  move_from_current_position_if_can(5 * M_PI / 4);
}

void Player::move_down_left() {
  move_from_current_position_if_can(3 * M_PI / 4);
}

void Player::shoot(Player &shot_player, Gun &gun) {
  int damage_got = gun.shoot(bullets);
  shot_player.receive_damage(damage_got);

}

bool Player::has_bullets(int amount) {
  return (bullets >= amount);
}

void Player::decrease_bullets(int amount) {
  bullets -= amount;
}

void Player::receive_damage(int amount) {
  health -= amount;
}

bool Player::add_gun_if_hasnt(Gun gun) {

  bool found = false;//(std::find(guns_bag.begin(), guns_bag.end(), gun) != guns_bag.end());
  if (!found){
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
