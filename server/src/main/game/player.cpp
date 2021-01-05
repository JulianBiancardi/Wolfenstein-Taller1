#include "player.h"
#include <cmath>

Player::Player(Point origin, double angle, int id) :
    shot_bullets(0), points(0), Moveable(origin, angle, id),
    Shooter(origin, angle) {
  max_health = ConfigLoader::player_health;
  health = max_health;
  max_bullets = 100; // TODO Use config loader
  bullets = ConfigLoader::player_bullets;
}

Player::Player(double x, double y, double angle, int id) :
    shot_bullets(0), points(0), Moveable(x, y, angle, id),
    Shooter(Point(x, y), angle) {
  max_health = ConfigLoader::player_health;
  health = max_health;
  max_bullets = 100; // TODO Use config loader
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

void Player::add_gun(const Gun gun) {
  guns_bag.push_back(gun);
}

bool Player::has_gun(const Gun gun) {
  return false;
}
/*
bool Player::add_gun_if_hasnt(Gun gun) {
  bool found =
      false;//(std::find(guns_bag.begin(), guns_bag.end(), gun) != guns_bag.end());
  if (!found) {
    guns_bag.push_back(gun);
    return true;
  }
  return false;
}
*/
void Player::add_points(int amount) {
  points += amount;
}

void Player::add_bullets(int amount) {
  if (bullets + amount < max_bullets) {
    bullets += amount;
  } else {
    bullets = max_bullets;
  }
}

void Player::add_health(int amount) {
  if (health + amount < max_health) {
    health += amount;
  } else {
    health = max_health;
  }
}
/*
bool Player::add_health_if_hass_less(int amount, int less_than) {
  if (health < less_than) {
    health += amount;
    return true;
  }
  return false;
}
*/

void Player::decrease_health(int amount) {
  if (health - amount <= 0) {
    health = 0; //Is_dead
  } else {
    health -= amount;
  }
}

bool Player::is_full_health() {
  return health == max_health;
}

int Player::get_health() {
  return health;
}
