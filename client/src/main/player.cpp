#include "player.h"

#include <cmath>
#include <utility>

#include "../../../common/src/main/ids/movement_ids.h"
#include "guns/knife.h"

Player::Player(Ray position)
    : position(position),
      guns_bag(),
      Object(position /*, position.get_angle()*/,
             new CircleMask(ConfigLoader::player_mask_radio,
                            position.get_ref_origin())) {
  pace = CL::player_pace;
  health = CL::player_health;
  bullets = CL::player_health;
  Knife* knife = new Knife();
  guns_bag.insert(std::pair<int, Gun*>(0, knife));
  active_gun = 0;
}

Player::Player(Point origin, double angle)
    : position(origin, angle),
      guns_bag(),
      Object(origin, angle,
             new CircleMask(ConfigLoader::player_mask_radio, origin)) {
  pace = CL::player_pace;
  health = CL::player_health;
  bullets = CL::player_health;
  Knife* knife = new Knife();
  guns_bag.insert(std::pair<int, Gun*>(0, knife));
  active_gun = 0;
}

Player::Player(double x, double y, double angle)
    : position(x, y, angle),
      guns_bag(),
      Object(Point(x, y), angle,
             new CircleMask(ConfigLoader::player_mask_radio, Point(x, y))) {
  pace = CL::player_pace;
  health = CL::player_health;
  bullets = CL::player_health;
  Knife* knife = new Knife();
  guns_bag.insert(std::pair<int, Gun*>(0, knife));
  active_gun = 0;
}

Player::~Player() {
  std::unordered_map<int, Gun*>::iterator iter;
  for (iter = guns_bag.begin(); iter != guns_bag.end(); iter++) {
    delete iter->second;
  }
}

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

  double next_x = position.get_origin().getX() + cos(movement_angle) * pace;
  double next_y = position.get_origin().getY() + sin(movement_angle) * pace;

  position = Ray(next_x, next_y, position.get_angle());
}

void Player::rotate(unsigned char direction) {
  switch (direction) {
    case LEFT_ROTATION:
      position = Ray(position.get_origin(),
                     position.get_angle() + CL::player_rotation_angle);
  }
}

Hit Player::shoot(Map& map) {
  return std::move(guns_bag[active_gun]->shoot(*this, bullets, map));
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