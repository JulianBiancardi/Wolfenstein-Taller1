#include "player.h"

#include "../../../../common/src/main/ids/gun_ids.h"
#include "collisions/circle_mask.h"

Player::Player(const Point& origin, double angle)
    : shot_bullets(0),
      points(0),
      guns_bag{KNIFE_ID, PISTOL_ID},
      spawn_point(origin),
      players_killed(0),
      keys(0),
      active_gun(PISTOL_ID),
      max_health(CL::player_health),
      health(max_health),
      max_bullets(CL::player_max_bullets),
      bullets(CL::player_bullets),
      lives(CL::player_lives),
      Moveable(origin, angle, CL::player_speed, CL::player_rotation_speed,
               CL::player_mask_radio) {}

Player::Player(const Point& origin, double angle, unsigned int id)
    : shot_bullets(0),
      points(0),
      guns_bag{KNIFE_ID, PISTOL_ID},
      spawn_point(origin),
      players_killed(0),
      keys(0),
      active_gun(PISTOL_ID),
      max_health(CL::player_health),
      health(max_health),
      max_bullets(CL::player_max_bullets),
      bullets(CL::player_bullets),
      lives(CL::player_lives),
      Moveable(origin, angle, CL::player_speed, CL::player_rotation_speed,
               CL::player_mask_radio, id) {}

Player::Player(double x, double y, double angle)
    : shot_bullets(0),
      points(0),
      guns_bag{KNIFE_ID, PISTOL_ID},
      spawn_point(x, y),
      players_killed(0),
      keys(0),
      active_gun(PISTOL_ID),
      max_health(CL::player_health),
      health(max_health),
      max_bullets(CL::player_max_bullets),
      bullets(CL::player_bullets),
      lives(CL::player_lives),
      Moveable(x, y, angle, CL::player_speed, CL::player_rotation_speed,
               CL::player_mask_radio) {}

Player::Player(const Player& player)
    : shot_bullets(player.shot_bullets),
      points(player.points),
      // guns_bag{KNIFE_ID, PISTOL_ID},
      spawn_point(player.get_position()),
      players_killed(player.players_killed),
      keys(player.keys),
      active_gun(PISTOL_ID),
      Moveable(player) {
  max_bullets = player.max_bullets;
  bullets = player.bullets;
  max_health = player.max_health;
  health = player.health;
  lives = player.lives;
  guns_bag = player.guns_bag;
}

Player::~Player() { }

void Player::remove_guns_to_respawn() {
  auto it = guns_bag.begin();
  while (it != guns_bag.end()) {
    if (*it != KNIFE_ID && *it != PISTOL_ID)
      it = guns_bag.erase(it);
    else
      it++;
  }
}

void Player::receive_damage(int amount) {
  health = std::max(0, health - amount);
}

void Player::add_gun(int gun_id) { guns_bag.insert(gun_id); }

bool Player::has_gun(int gun_id) const {
  return guns_bag.find(gun_id) != guns_bag.end();
}

bool Player::has_droppable_gun() {
  bool has_droppable_gun = false;
  for (auto it = guns_bag.begin(); it != guns_bag.end() && !has_droppable_gun;
       it++) {
    if (*it != KNIFE_ID && *it != PISTOL_ID) has_droppable_gun = true;
  }
  return has_droppable_gun;
}

bool Player::change_gun(int gun_id) {
  if (!this->has_gun(gun_id)) {
    return false;
  }

  active_gun = gun_id;
  return true;
}

bool Player::shoot() {
  int bullets_shot;

  switch (active_gun) {
    case PISTOL_ID:
      bullets_shot = CL::pistol_bullet_required;
      break;
    case MACHINE_GUN_ID:
      bullets_shot = CL::machine_gun_bullet_required;
      break;
    case CHAIN_CANNON_ID:
      bullets_shot = CL::chain_cannon_bullet_required;
      break;
    case KNIFE_ID:
      bullets_shot = 0;
      break;
    case ROCKET_LAUNCHER_ID:
      bullets_shot = CL::rocket_launcher_bullet_required;
      break;
    default:
      return false;
  }

  if (bullets - bullets_shot < 0) {
    return false;
  }

  bullets -= bullets_shot;
  shot_bullets += bullets_shot;
  return true;
}

void Player::remove_key() {
  if (has_keys()) {
    keys--;
  }
}

bool Player::is_full_health() const { return health == max_health; }

bool Player::is_full_bullets() const { return bullets == max_bullets; }

bool Player::is_dead() const { return health == 0; }

bool Player::has_extra_lives() const { return lives > 1; }

bool Player::has_keys() const { return keys != 0; }

void Player::respawn() {
  lives--;
  remove_guns_to_respawn();
  active_gun = PISTOL_ID;
  keys = 0;
  bullets = ConfigLoader::player_respawn_bullets;
  health = ConfigLoader::player_health;
  position = Ray(spawn_point, 0);
}

bool Player::is_using_rocket_launcher() const {
  return active_gun == ROCKET_LAUNCHER_ID;
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

void Player::add_key() { keys++; }

void Player::add_kill() { players_killed++; }

int Player::get_health() const { return health; }

int Player::get_bullets() const { return bullets; }

int Player::get_active_gun() const { return active_gun; }

int Player::get_kills() const { return players_killed; }

int Player::get_lives() const { return lives; }

int Player::get_points() const { return points; }
