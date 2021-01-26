#include "player.h"

#include <cmath>
#include <utility>

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

Point Player::next_position(double direction_angle) {
  double movement_angle = position.get_angle() + direction_angle;

  double next_x = position.get_origin().getX() + cos(movement_angle) * pace;
  double next_y = position.get_origin().getY() + sin(movement_angle) * pace;

  return Point(next_x, next_y);
}

Point Player::next_position_up() { return next_position(0); }

Point Player::next_position_down() { return next_position(M_PI); }

Point Player::next_position_right() { return next_position(3 * M_PI / 2); }

Point Player::next_position_left() { return next_position(M_PI / 2); }

Point Player::next_position_up_right() { return next_position(7 * M_PI / 4); }

Point Player::next_position_up_left() { return next_position(M_PI / 4); }

Point Player::next_position_down_right() { return next_position(5 * M_PI / 4); }

Point Player::next_position_down_left() { return next_position(3 * M_PI / 4); }

void Player::set_position(const Point& new_origin) {
  position = Ray(new_origin, position.get_angle());
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