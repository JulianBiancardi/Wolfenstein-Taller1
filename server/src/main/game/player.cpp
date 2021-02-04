#include "player.h"

#include "../../../../common/src/main/ids/gun_ids.h"

Player::Player(Point origin, double angle)
    : shot_bullets(0),
      points(0),
      guns_bag{KNIFE_ID, PISTOL_ID},
      spawn_point(origin),
      players_killed(0),
      keys(0),
      active_gun(PISTOL_ID),
      knife_mask(new CircleMask(ConfigLoader::player_knife_mask_radio,
                                position.get_ref_origin())),
      Moveable(origin, angle) {
  knife_mask = new CircleMask(ConfigLoader::player_knife_mask_radio,
      position.get_ref_origin());
  max_health = ConfigLoader::player_health;
  health = max_health;
  max_bullets = ConfigLoader::player_max_bullets;
  bullets = ConfigLoader::player_bullets;
  lives = ConfigLoader::player_lives;
}

Player::Player(double x, double y, double angle)
    : shot_bullets(0),
      points(0),
      guns_bag{KNIFE_ID, PISTOL_ID},
      spawn_point(x, y),
      players_killed(0),
      keys(0),
      active_gun(PISTOL_ID),
      knife_mask(new CircleMask(ConfigLoader::player_knife_mask_radio,
                                position.get_ref_origin())),
      Moveable(x, y, angle) {
  knife_mask = new CircleMask(ConfigLoader::player_knife_mask_radio,
                              position.get_ref_origin());
  max_health = ConfigLoader::player_health;
  health = max_health;
  max_bullets = ConfigLoader::player_max_bullets;
  bullets = ConfigLoader::player_bullets;
  lives = ConfigLoader::player_lives;
}

Player::~Player() { delete knife_mask; }

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

// PRECONDITION: Keeping the amount of bullets a valid amount is responsibility
// of the client (shooting logic is in the client).
void Player::shoot() {
  int bullets_shot;

  // TODO Try to optimize when testing
  switch (active_gun) {
    case KNIFE_ID:bullets_shot = 0;
      break;
    case PISTOL_ID:bullets_shot = CL::pistol_bullet_required;
      break;
    case MACHINE_GUN_ID:bullets_shot = CL::machine_gun_bullet_required;
      break;
    case CHAIN_CANNON_ID:bullets_shot = CL::chain_cannon_bullet_required;
      break;
    case ROCKET_LAUNCHER_ID:bullets_shot = CL::rocket_launcher_bullet_required;
      break;
    default:bullets_shot = 0;
  }

  bullets -= bullets_shot;
  shot_bullets += bullets_shot;
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

void Player::remove_key() { keys--; }

bool Player::is_full_health() const { return health == max_health; }

bool Player::is_full_bullets() { return bullets == max_bullets; }

bool Player::is_dead() const { return health == 0; }

bool Player::has_extra_lives() { return lives > 1; }

bool Player::has_keys() const { return keys != 0; }

void Player::respawn() {
  lives--;
  remove_guns_to_respawn();
  active_gun = PISTOL_ID;
  keys = 0;
  bullets = ConfigLoader::player_respawn_bullets;
  health = ConfigLoader::player_health;
  position = Ray(spawn_point, 0);  // TODO Angle is not 0
}

int Player::get_health() const { return health; }

int Player::get_bullets() const { return bullets; }

int Player::get_active_gun() const { return active_gun; }

int Player::get_kills() { return players_killed; }

int Player::get_lives() { return lives; }

int Player::get_points() const { return points; }

void Player::add_kill() { players_killed++; }

void Player::remove_guns_to_respawn() {
  auto it = guns_bag.begin();
  while (it != guns_bag.end()) {
    if (*it != KNIFE_ID && *it != PISTOL_ID)
      it = guns_bag.erase(it);
    else
      it++;
  }
}
Player::Player(const Player& player)
    : shot_bullets(player.shot_bullets),
      points(player.points),
    //guns_bag{KNIFE_ID, PISTOL_ID},
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
  this->knife_mask = new CircleMask(ConfigLoader::player_knife_mask_radio,
                              position.get_ref_origin());
}
Point Player::knife_collision_mask_bound(const Point& next_position) const{
  double angle = position.get_origin().angle_to(next_position);

  double front_x =
      next_position.getX()
          + cos(angle) * ((CircleMask*) knife_mask)->get_radius();
  double front_y =
      next_position.getY()
          - sin(angle) * ((CircleMask*) knife_mask)->get_radius();

  return Point(front_x, front_y);
}

bool Player::knife_mask_bound_occupies(const Point& where) const {
  return knife_mask->occupies(where);
}