#include "player.h"

Player::Player(Point origin, double angle)
    : shot_bullets(0),
      points(0),
      spawn_point(origin),
      players_killed(0),
      Moveable(origin, angle) {
  max_health = ConfigLoader::player_health;
  health = max_health;
  max_bullets = ConfigLoader::player_max_bullets;
  bullets = ConfigLoader::player_bullets;
  lives = ConfigLoader::player_lives;
}

Player::Player(double x, double y, double angle)
    : shot_bullets(0),
      points(0),
      spawn_point(x, y),
      players_killed(0),
      Moveable(x, y, angle) {
  max_health = ConfigLoader::player_health;
  health = max_health;
  max_bullets = ConfigLoader::player_max_bullets;
  bullets = ConfigLoader::player_bullets;
  lives = ConfigLoader::player_lives;
}

void Player::receive_damage(int amount) {
  if (health - amount <= 0) {
    health = 0;
  } else {
    health -= amount;
  }
}

void Player::add_gun(int gun_id) { guns_bag.insert(gun_id); }

bool Player::has_gun(int gun_id) {
  return guns_bag.find(gun_id) != guns_bag.end();
}

void Player::change_gun(int gun_id) {
  if (this->has_gun(gun_id))
    active_gun = gun_id;
}

void Player::shoot(Player& enemy_shot, double damage_done, int bullets_shot) {
  enemy_shot.receive_damage(damage_done);
  this->decrease_bullets(bullets_shot);
}

void Player::add_bullets(int amount) {
  if (bullets + amount < max_bullets) {
    bullets += amount;
  } else {
    bullets = max_bullets;
  }
}

void Player::add_points(int amount) { points += amount; }

void Player::add_health(int amount) {
  if (health + amount < max_health) {
    health += amount;
  } else {
    health = max_health;
  }
}

// PRECONDITION: Keeping the amount of bullets a valid amount is responsibility
// of the client (shooting logic is in the client).
void Player::decrease_bullets(int amount) {
  bullets -= amount;
  shot_bullets += amount;
}

bool Player::is_full_health() { return health == max_health; }

bool Player::is_full_bullets() { return bullets == max_bullets; }

bool Player::is_dead() { return health == 0; }

bool Player::has_lives_left() {
  return lives != 0;
}

void Player::respawn() {
  lives--;
  // TODO Add gun removal
  bullets = ConfigLoader::player_respawn_bullets;
  position.get_origin() = spawn_point;
}

int Player::get_health() { return health; }

int Player::get_bullets() { return bullets; }

int Player::get_active_gun() { return active_gun; }

int Player::get_kills() { return players_killed; }

void Player::add_kill() { players_killed++; }
