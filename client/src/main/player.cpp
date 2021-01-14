#include "player.h"

#include <cmath>

#include "casting/ray_casting.h"

Player::Player(Ray position, Gun& gun) :
    position(position), active_gun(gun),
    Object(position/*, position.get_angle()*/,
           new Circle_mask
           (ConfigLoader::player_mask_radio, position.get_ref_origin())) {
  pace = 1;  // TODO Use config file
  health = CL::player_health;
  bullets = CL::player_health;
}

Player::Player(Point origin, double angle, Gun& gun) :
    position(origin, angle), active_gun(gun) ,
    Object(origin, angle,
           new Circle_mask
               (ConfigLoader::player_mask_radio, origin)) {
  pace = 1;  // TODO Use config file
  health = CL::player_health;
  bullets = CL::player_health;
}

Player::Player(double x, double y, double angle, Gun& gun) :
    position(x, y, angle), active_gun(gun) ,
    Object(Point(x,y), angle,
           new Circle_mask
               (ConfigLoader::player_mask_radio, Point(x,y))) {
  pace = 1;  // TODO Use config file
  health = CL::player_health;
  bullets = CL::player_health;
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


void Player::shoot(Map& map) {
  active_gun.shoot(*this, bullets, map);
}

void Player::set_gun(Gun& gun) {
  active_gun = gun;
}

//
void Player::set_health(int health) { this->health = health; }
int Player::get_health() { return this->health; }

bool Player::has_bullets(int amount) { return (bullets >= amount); }

void Player::decrease_bullets(int amount) {
  bullets -= amount;
}
Player::~Player() {}