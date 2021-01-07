#include "player.h"

#include <cmath>

// Move to Gun if shoot gets delegated
#include "../../../../common/src/main/casting/ray_casting.h"
#include "../../../../common/src/main/utils/ray.h"
#include "../map.h"

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

void Player::shoot(Map& map) {
  double angle = position.get_angle();
  Ray bullet = position;  // TODO Make some probabilistic shot
  double wall_distance =
      RayCasting::get_collision(map, bullet).get_distance_from_src();

  std::vector<Object> objects = map.get_objects();
  // TODO Sort objects from closest to farthest, to only hit closest.
  std::vector<Object>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    Object& object = *iter;
    // TODO Consider: if (!object.is_solid()) {continue;}
    double object_distance =
        object.get_position().distance_from(position.get_origin());
    // This can be used to limit weapon range
    if (object_distance >= wall_distance) {
      continue;
    }

    // As a decision of implementation design, solid objects have same radius
    // TODO Change number 1 to use ConfigLoader and use the actual size of
    // things.
    double half_angular_diameter = atan(1 / object_distance);
    double object_angle = object.get_position().angle_to(position.get_origin());

    double left_angle = object_angle + half_angular_diameter;
    if (left_angle > 2 * M_PI) {
      left_angle -= 2 * M_PI;
    }

    double right_angle = object_angle - half_angular_diameter;
    if (right_angle < 0) {
      right_angle += 2 * M_PI;
    }

    // Check if bullet angle is between object angular diameter
    double rel_angle =
        std::fmod(std::fmod(left_angle - right_angle, 360) + 360, 360);
    if (rel_angle >= 180) {
      std::swap(left_angle, right_angle);
    }

    bool hit = false;
    double bullet_angle = bullet.get_angle();
    if (right_angle <= left_angle) {
      hit = bullet_angle >= right_angle && bullet_angle <= left_angle;
    } else {
      hit = bullet_angle >= right_angle || bullet_angle <= left_angle;
    }
    // TODO We know we hit the object. Proceed with whatever is necessary.
  }
}

/*void Player::shoot_player(Player &shot_player, Gun &gun) {
//  shoot_checker();
  int damage_got = gun.shoot(bullets);
  shot_player.receive_damage(damage_got);
}*/

bool Player::has_bullets(int amount) { return (bullets >= amount); }
/*
void Player::decrease_bullets(int amount) {
  bullets -= amount;
}
*/
void Player::receive_damage(int amount) { health -= amount; }

void Player::add_gun(const Gun gun) { guns_bag.push_back(gun); }

bool Player::has_gun(const Gun gun) { return false; }
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

int Player::get_health() { return health; }
