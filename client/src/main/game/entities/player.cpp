#include "player.h"

#include <cmath>
#include <utility>

#include "../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../common/src/main/ids/images_ids.h"
#include "../../../../../common/src/main/ids/map_ids.h"
#include "../guns/chain_cannon.h"
#include "../guns/knife.h"
#include "../guns/machine_gun.h"
#include "../guns/pistol.h"
#include "../guns/rocket_launcher.h"

Player::Player(const Ray& position, unsigned int player_id)
    : guns_bag(),
      IdentifiableObject(position, 1, player_id),
      spawn_point(position.get_ref_origin()) {
  lives = CL::player_lives;
  health = CL::player_health;
  bullets = CL::player_bullets;
  points = 0;
  keys = 0;
  guns_bag.reserve(GUN_AMOUNT);
  std::unique_ptr<Gun> knife(new Knife(HUD_KNIFE_SHOOT));
  std::unique_ptr<Gun> pistol(new Pistol(HUD_PISTOL_SHOOT));
  guns_bag.insert(std::make_pair(KNIFE_ID, std::move(knife)));
  guns_bag.insert(std::make_pair(PISTOL_ID, std::move(pistol)));
  active_gun = PISTOL_ID;
  previous_gun = 0;
  players_killed = 0;
  speed = CL::player_speed;
}

Player::~Player() = default;

void Player::remove_guns_to_respawn() {
  auto it = guns_bag.begin();
  while (it != guns_bag.end()) {
    if (it->first != KNIFE_ID && it->first != PISTOL_ID) {
      it = guns_bag.erase(it);
    } else {
      it++;
    }
  }
}

int Player::get_lives() const { return lives; }
int Player::get_health() const { return health; }
int Player::get_percentage_health() const {
  return (health * 100 / CL::player_health);
}
int Player::get_gun() const { return active_gun; }
int Player::get_bullets() const { return bullets; }
int Player::get_points() const { return points; }
bool Player::has_key() const { return keys > 0; }
Gun* Player::get_active_gun() const { return guns_bag.at(active_gun).get(); }

void Player::move(unsigned char direction) {
  double movement_angle = position.get_angle();

  switch (direction) {
    case UP:
      break;
    case UP_LEFT:
      movement_angle += (M_PI / 4);
      break;
    case LEFT:
      movement_angle += (M_PI / 2);
      break;
    case DOWN_LEFT:
      movement_angle += (3 * M_PI / 4);
      break;
    case DOWN:
      movement_angle += M_PI;
      break;
    case DOWN_RIGHT:
      movement_angle += (5 * M_PI / 4);
      break;
    case RIGHT:
      movement_angle += (3 * M_PI / 2);
      break;
    case UP_RIGHT:
      movement_angle += (7 * M_PI / 4);
      break;
  }

  double next_x = position.get_origin().getX() + cos(movement_angle) * speed;
  double next_y = position.get_origin().getY() - sin(movement_angle) * speed;

  position = Ray(next_x, next_y, position.get_angle());
  state.move();
}

void Player::rotate(unsigned char direction) {
  switch (direction) {
    case LEFT_ROTATION:
      position = Ray(position.get_origin(),
                     position.get_angle() + CL::player_rotation_speed);
      break;
    case RIGHT_ROTATION:
      position = Ray(position.get_origin(),
                     position.get_angle() - CL::player_rotation_speed);
      break;
    default:
      break;
  }
}

Hit Player::update_gun(
    BaseMap& map, bool trigger,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  return std::move(guns_bag[active_gun]->update(*this, trigger, map, players));
}

bool Player::has_droppable_gun() {
  bool has_droppable_gun = false;
  for (auto it = guns_bag.begin(); it != guns_bag.end() && !has_droppable_gun;
       it++) {
    if (it->first != KNIFE_ID && it->first != PISTOL_ID) {
      has_droppable_gun = true;
    }
  }
  return has_droppable_gun;
}

bool Player::has_keys() const { return keys != 0; }

unsigned int Player::get_kills() const { return players_killed; }

void Player::set_gun(int gun_num) {
  if (guns_bag.find(gun_num) != guns_bag.end()) {
    active_gun = gun_num;
  }
}

void Player::decrease_bullets(unsigned char gun_id) {
  switch (gun_id) {
    case PISTOL_ID:
      bullets -= CL::pistol_bullet_required;
      break;
    case MACHINE_GUN_ID:
      bullets -= CL::machine_gun_bullet_required;
      break;
    case CHAIN_CANNON_ID:
      bullets -= CL::chain_cannon_bullet_required;
      break;
    case ROCKET_LAUNCHER_ID:
      bullets -= CL::rocket_launcher_bullet_required;
      break;
    default:
      break;
  }

  bullets = std::max(bullets, 0);
}

bool Player::is_dead() const { return health == 0; }

bool Player::has_lives_left() const { return lives > 1; }

void Player::respawn() {
  lives--;
  remove_guns_to_respawn();
  active_gun = PISTOL_ID;
  keys = 0;
  bullets = CL::player_respawn_bullets;
  health = CL::player_health;
  position = Ray(spawn_point, 0);
}

void Player::add_kill() {
  players_killed++;
  add_points(CL::kill_points);
}

void Player::respawn_as_ghost() {
  lives--;
  state.become_ghost();
  keys = 0;
  bullets = 0;
  position = Ray(spawn_point, 0);
  speed = CL::player_ghost_speed;
}

void Player::add_gun(unsigned int gun_id) {
  switch (gun_id) {
    case MACHINE_GUN_ID: {
      Gun* machine_gun = new MachineGun(HUD_MACHINEGUN_SHOOT);
      guns_bag.insert(std::make_pair(MACHINE_GUN_ID, std::move(machine_gun)));
      break;
    }
    case CHAIN_CANNON_ID: {
      Gun* chain_cannon = new ChainCannon(HUD_CHAINCANNON_SHOOT);
      guns_bag.insert(std::make_pair(CHAIN_CANNON_ID, std::move(chain_cannon)));
      break;
    }
    case ROCKET_LAUNCHER_ID: {
      Gun* rocket_launcher = new RocketLauncher(HUD_ROCKETLAUNCHER_SHOOT);
      guns_bag.insert(
          std::make_pair(ROCKET_LAUNCHER_ID, std::move(rocket_launcher)));
      break;
    }
    default:;
      break;
  }
}

void Player::add_points(unsigned int added_points) {
  if ((points + added_points) <= CL::player_max_points) {
    points += added_points;
  } else {
    points = CL::player_max_points;
  }
}

void Player::add_health(unsigned int added_health) {
  health = std::min(CL::player_health, (int)(health + added_health));
}

void Player::add_bullets(unsigned int added_bullets) {
  bullets = std::min(CL::player_max_bullets, (int)(bullets + added_bullets));
}

void Player::decrease_health(unsigned int lost_health) {
  health = std::max(0, (int)(health - lost_health));
}

void Player::add_key() { keys++; }

void Player::use_key() { keys--; }

bool Player::has_bullets_to_shoot_gun() const {
  switch (active_gun) {
    case KNIFE_ID:
      return true;
    case PISTOL_ID:
      return bullets >= CL::pistol_bullet_required;
    case MACHINE_GUN_ID:
      return bullets >= CL::machine_gun_bullet_required;
    case CHAIN_CANNON_ID:
      return bullets >= CL::chain_cannon_bullet_required;
    case ROCKET_LAUNCHER_ID:
      return bullets >= CL::rocket_launcher_bullet_required;
    default:
      return false;
  }
}

void Player::remember_gun() { previous_gun = active_gun; }

void Player::use_previous_gun_if_has_to() {
  if (previous_gun != 0) {
    active_gun = previous_gun;

    if (!has_bullets_to_shoot_gun()) {
      active_gun = KNIFE_ID;
    } else {
      previous_gun = 0;
    }
  }
}

void Player::update() { state.update(); }

Image* Player::get_image(ResourceManager& resource_manager) {
  switch (active_gun) {
    case KNIFE_ID:
      return resource_manager.get_image(DOG);
    case PISTOL_ID:
      return resource_manager.get_image(GUARD);
    case MACHINE_GUN_ID:
      return resource_manager.get_image(SCHUTZSTAFFEL);
    case CHAIN_CANNON_ID:
      return resource_manager.get_image(OFFICER);
    case ROCKET_LAUNCHER_ID:
      return resource_manager.get_image(MUTANT);
    default:
      return nullptr;
  }
}

SDL_Rect* Player::get_slice(void* extra) {
  double angle_of_perception =
      Angle::normalize(*(double*)extra - position.get_angle() + M_PI / 8);
  state.set_slice(slice, angle_of_perception);
  return &slice;
}
