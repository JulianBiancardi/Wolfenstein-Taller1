#include "player.h"

#include <cmath>
#include <utility>

#include "../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../common/src/main/ids/map_ids.h"
#include "../../../../../common/src/main/ids/movement_ids.h"
#include "../guns/chain_cannon.h"
#include "../guns/knife.h"
#include "../guns/machine_gun.h"
#include "../guns/pistol.h"
#include "../guns/rocket_launcher.h"

Player::Player(Ray position, unsigned int player_id)
    : guns_bag(), Object(GUARD, position, player_id) {
  lives = CL::player_lives;
  health = CL::player_health;
  bullets = CL::player_bullets;
  points = 0;
  keys = 0;
  std::shared_ptr<Gun> knife(new Knife());
  std::shared_ptr<Gun> pistol(new Pistol());
  guns_bag.insert(std::make_pair(KNIFE_ID, std::move(knife)));
  guns_bag.insert(std::make_pair(PISTOL_ID, std::move(pistol)));
  active_gun = 2;
}

/*
Player::Player(const Player& other) : Object(other) {
  this->pace = other.pace;
  this->health = other.health;
  this->bullets = other.bullets;
  this->guns_bag = other.guns_bag;
  this->active_gun = other.active_gun;
}
Player& Player::operator=(const Player& other) {
  if (this != &other) {
    Object::operator=(other);
    this->pace = other.pace;
    this->health = other.health;
    this->bullets = other.bullets;
    this->guns_bag = other.guns_bag;
    this->active_gun = other.active_gun;
  }

  return *this;
}

Player::Player(Player&& other) : Object(std::move(other)) {
  this->pace = other.pace;
  this->health = other.health;
  this->bullets = other.bullets;
  this->guns_bag = std::move(other.guns_bag);
  this->active_gun = other.active_gun;

  other.pace = 0;
  other.health = 0;
  other.bullets = 0;
  other.active_gun = 0;
}

Player& Player::operator=(Player&& other) {
  if (this == &other) {
    return *this;
  }

  Object::operator=(std::move(other));
  this->pace = other.pace;
  this->health = other.health;
  this->bullets = other.bullets;
  this->guns_bag = std::move(other.guns_bag);
  this->active_gun = other.active_gun;

  other.pace = 0;
  other.health = 0;
  other.bullets = 0;
  other.active_gun = 0;

  return *this;
}*/

Player::~Player() {}

int Player::get_lives() const { return lives; }
int Player::get_health() const { return health; }
int Player::get_gun() const { return active_gun; }
int Player::get_bullets() const { return bullets; }
int Player::get_points() const { return points; }

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

  double next_x =
      position.get_origin().getX() + cos(movement_angle) * CL::player_speed;
  double next_y =
      position.get_origin().getY() - sin(movement_angle) * CL::player_speed;

  position = Ray(next_x, next_y, position.get_angle());
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

Hit Player::trigger_gun(
    BaseMap& map, const std::vector<std::shared_ptr<Object>>& map_objects) {
  return std::move(
      guns_bag.at(active_gun)->trigger(*this, bullets, map, map_objects));
}

void Player::untrigger_gun() { guns_bag[active_gun]->untrigger(); }

void Player::set_gun(int gun_num) {
  if (guns_bag.find(gun_num) != guns_bag.end()) {
    active_gun = gun_num;
  }
}

void Player::set_health(int health) { this->health = health; }

bool Player::has_bullets(int amount) { return (bullets >= amount); }

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

void Player::grab_item(Object& item) {
  switch (item.get_type()) {
    case GUNS_TYPE:
      add_gun(item.get_res_id());
      break;
    case ITEMS_TYPE:
      add_item(item.get_res_id());
      break;
  }
}

void Player::add_gun(unsigned int gun_id) {
  switch (gun_id) {
    case MACHINE_GUN: {
      std::shared_ptr<Gun> machine_gun(new MachineGun());
      guns_bag.insert(std::make_pair(MACHINE_GUN_ID, std::move(machine_gun)));
      break;
    }
    case CHAIN_CANNON: {
      std::shared_ptr<Gun> chain_cannon(new ChainCannon());
      guns_bag.insert(std::make_pair(CHAIN_CANNON_ID, std::move(chain_cannon)));
      break;
    }
    case ROCKET_LAUNCHER_ID: {
      // std::shared_ptr<Gun> rocket_launcher(new RocketLauncher());
      // guns_bag.insert(std::make_pair(5, std::move(rocket_launcher)));
      break;
    }
    default:;
      break;
  }
}

void Player::add_item(unsigned int item_id) {
  switch (item_id) {
    case FOOD:
      health = std::min(CL::player_health, health + CL::food_health_recovered);
      break;
    case MEDKIT:
      health =
          std::min(CL::player_health, health + CL::medic_kit_health_recovered);
      break;
    case BLOOD:
      health = CL::player_health + CL::blood_health_recovered;
      break;
    case BULLETS:
      bullets = std::min(CL::player_max_bullets, bullets + CL::bullets_amount);
      break;
    case CROSS:
      points += CL::crosses_points;
      break;
    case CUP:
      points += CL::cup_points;
      break;
    case CHEST:
      points += CL::chests_points;
      break;
    case CROWN:
      points += CL::crown_points;
      break;
    case KEY:
      keys += 1;
      break;
  }
}