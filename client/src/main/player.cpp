#include "player.h"

#include <cmath>
#include <utility>

#include "../../../common/src/main/ids/map_ids.h"
#include "../../../common/src/main/ids/movement_ids.h"
#include "guns/knife.h"

<<<<<<< HEAD
Player::Player(Ray position, unsigned int player_id)
    : guns_bag(), Object(GUARD, position, player_id) {
  pace = CL::player_pace;
=======
Player::Player(Ray position)
    : guns_bag(),
      Object(position, new CircleMask(ConfigLoader::player_mask_radio,
                                      position.get_ref_origin())) {
  pace = CL::player_speed;
  health = CL::player_health;
  bullets = CL::player_health;
  Knife* knife = new Knife();
  guns_bag.insert(std::pair<int, Gun*>(0, knife));
  active_gun = 0;
}

Player::Player(Ray position, unsigned int player_id)
    : guns_bag(),
      Object(position,
             new CircleMask(ConfigLoader::player_mask_radio,
                            position.get_ref_origin()),
             player_id) {
  pace = CL::player_speed;
  health = CL::player_health;
  bullets = CL::player_health;
  Knife* knife = new Knife();
  guns_bag.insert(std::pair<int, Gun*>(0, knife));
  active_gun = 0;
}

Player::Player(Point origin, double angle)
    : guns_bag(),
      Object(origin, angle,
             new CircleMask(ConfigLoader::player_mask_radio, origin)) {
  pace = CL::player_speed;
  health = CL::player_health;
  bullets = CL::player_health;
  Knife* knife = new Knife();
  guns_bag.insert(std::pair<int, Gun*>(0, knife));
  active_gun = 0;
}

Player::Player(Point origin, double angle, unsigned int player_id)
    : guns_bag(),
      Object(origin, angle,
             new CircleMask(ConfigLoader::player_mask_radio, origin),
             player_id) {
  pace = CL::player_speed;
  health = CL::player_health;
  bullets = CL::player_health;
  Knife* knife = new Knife();
  guns_bag.insert(std::pair<int, Gun*>(0, knife));
  active_gun = 0;
}

Player::Player(double x, double y, double angle)
    : guns_bag(),
      Object(Point(x, y), angle,
             new CircleMask(ConfigLoader::player_mask_radio, Point(x, y))) {
  pace = CL::player_speed;
  health = CL::player_health;
  bullets = CL::player_health;
  Knife* knife = new Knife();
  guns_bag.insert(std::pair<int, Gun*>(0, knife));
  active_gun = 0;
}

Player::Player(double x, double y, double angle, unsigned int player_id)
    : guns_bag(),
      Object(Point(x, y), angle,
             new CircleMask(ConfigLoader::player_mask_radio, Point(x, y)),
             player_id) {
  pace = CL::player_speed;
>>>>>>> 8cce666cb6cc761010e415fe6d411727b4f6af0a
  health = CL::player_health;
  bullets = CL::player_health;
  Knife* knife = new Knife();
  // FIXME Create with gun
  guns_bag.insert(std::pair<int, Gun*>(0, knife));
  active_gun = 0;
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

Player::~Player() {
  std::unordered_map<int, Gun*>::iterator iter;
  for (iter = guns_bag.begin(); iter != guns_bag.end(); iter++) {
    delete iter->second;
  }
}

void Player::move(unsigned char direction) {
  double movement_angle = position.get_angle();
  switch (direction) {
    case UP:break;
    case UP_LEFT:movement_angle += (M_PI / 4);
      break;
    case LEFT:movement_angle += (M_PI / 2);
      break;
    case DOWN_LEFT:movement_angle += (3 * M_PI / 4);
      break;
    case DOWN:movement_angle += M_PI;
      break;
    case DOWN_RIGHT:movement_angle += (5 * M_PI / 4);
      break;
    case RIGHT:movement_angle += (3 * M_PI / 2);
      break;
    case UP_RIGHT:movement_angle += (7 * M_PI / 4);
      break;
  }

  double next_x = position.get_origin().getX() + cos(movement_angle) * pace;
  double next_y = position.get_origin().getY() - sin(movement_angle) * pace;

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
    default:break;
  }
}

Hit Player::shoot(BaseMap& map, const std::vector<Object*>& map_objects) {
  return std::move(
      guns_bag[active_gun]->shoot(*this, bullets, map, map_objects));
}

void Player::add_gun(int gun_num, Gun* gun) {
  guns_bag.insert(std::pair<int, Gun*>(gun_num, gun));
}

void Player::set_gun(int gun_num) {
  if (guns_bag.find(gun_num) != guns_bag.end()) {
    active_gun = gun_num;
  }
}

void Player::set_health(int health) { this->health = health; }

int Player::get_health() { return this->health; }

bool Player::has_bullets(int amount) { return (bullets >= amount); }

void Player::decrease_bullets(int amount) { bullets -= amount; }