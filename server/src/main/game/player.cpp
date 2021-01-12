#include "player.h"

#include <cmath>

#include "../../../../common/src/main/utils/ray.h"  // TODO Check if not already included

Player::Player(Point origin, double angle, int id)
    : shot_bullets(0), points(0), Moveable(origin, angle, id) {
  max_health = ConfigLoader::player_health;
  health = max_health;
  max_bullets = 100;  // TODO Use config loader
  bullets = ConfigLoader::player_bullets;
}

Player::Player(double x, double y, double angle, int id)
    : shot_bullets(0), points(0), Moveable(x, y, angle, id) {
  max_health = ConfigLoader::player_health;
  health = max_health;
  max_bullets = 100;  // TODO Use config loader
  bullets = ConfigLoader::player_bullets;
}
/*
bool Player::has_bullets(int amount) { return (bullets >= amount); }

void Player::decrease_bullets(int amount) {
  bullets -= amount;
}
*/

void Player::receive_damage(int amount) { health -= amount; }

void Player::add_gun(int gun_id) { guns_bag.insert(gun_id); }

bool Player::has_gun(int gun_id) {
  return guns_bag.find(gun_id) != guns_bag.end();
}

// TODO This shouldn't be necessary. unordered_map.insert already checks if it
// is included
/*
bool Player::add_gun_if_hasnt(Gun gun) {
  bool found =
      false;//(std::find(guns_bag.begin(), guns_bag.end(), gun) !=
guns_bag.end()); if (!found) { guns_bag.push_back(gun); return true;
  }
  return false;
}
*/

void Player::add_points(int amount) { points += amount; }

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
    health = 0;  // Is_dead
  } else {
    health -= amount;
  }
}

bool Player::is_full_health() { return health == max_health; }

int Player::get_current_health() { return health; } //todo change to get_health
