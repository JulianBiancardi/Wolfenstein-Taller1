#include "player.h"
#include <cmath>

Player::Player(Point origin, double angle, Map &game_map) :
    shot_bullets(0), points(0), Moveable(origin, angle, game_map, 1) {
  health = ConfigLoader::player_health;
  //health = 100;
  bullets = ConfigLoader::player_bullets;
  //bullets = 8;
}

Player::Player(double x, double y, double angle, Map &game_map) :
    shot_bullets(0), points(0), Moveable(Point(x, y), angle, game_map, 1) {
  health = ConfigLoader::player_health;
  //health = 100;
  bullets = ConfigLoader::player_bullets;
  //bullets = 8;
}

void Player::shoot_checker(double direction_angle) {
/*
  Ray first_ray_cone(angled_position.get_origin(),
                     angled_position.get_angle()+direction_angle-M_PI/12);
  Ray second_ray_cone(angled_position.get_origin(),
                      angled_position.get_angle()+direction_angle+M_PI/12);



  double next_x = angled_position.get_origin().getX() +
      cos(angled_position.get_angle() + direction_angle) * pace;
  double next_y = angled_position.get_origin().getY() +
      sin(angled_position.get_angle() + direction_angle) * pace;

  if (!map.is_wall(next_x, next_y))
    angled_position.set_origin(next_x, next_y);
    */
}

void Player::shoot(Player &shot_player, Gun &gun) {
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
