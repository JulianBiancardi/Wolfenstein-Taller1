#include "player.h"

Player::Player(Point origin, double angle) :
        angled_position(origin,angle), shot_bullets(0), points(0){
    health = ConfigLoader::get_init_configs().player_health;
    bullets = ConfigLoader::get_init_configs().player_bullets;
}

Player::Player(int x, int y, double angle) :
        angled_position(x,y,angle), shot_bullets(0), points(0){
    health = ConfigLoader::get_init_configs().player_health;
    bullets = ConfigLoader::get_init_configs().player_bullets;
}


void Player::move_from_current_position_if_can(int x, int y){
  Ray next_position(angled_position.get_origin().getX() + x, 
                    angled_position.get_origin().getY() + y, 
                    angled_position.get_angle());
  if(Map::get_map().can_move_to(next_position.get_origin()))
    angled_position = next_position;  
}

void Player::move_up(){
  move_from_current_position_if_can(0, -1);
}

void Player::move_down(){
  move_from_current_position_if_can(0, 1);
}

void Player::move_right(){
  move_from_current_position_if_can(1, 0);
}

void Player::move_left(){
  move_from_current_position_if_can(-1, 0);
}

void Player::move_up_right(){
  move_from_current_position_if_can(1, -1);
}

void Player::move_up_left(){
  move_from_current_position_if_can(-1, -1);
}

void Player::move_down_right(){
  move_from_current_position_if_can(1, 1);
}

void Player::move_down_left(){
  move_from_current_position_if_can(-1, 1);
}

void Player::shoot() {

}

bool Player::has_bullets(int amount) {
    return (bullets>=amount);
}

void Player::decrease_bullets(int amount) {
    bullets-=amount;
}

void Player::receive_damage(int amount) {
    health-=amount;
}

//bool Player::add_gun_if_hasnt(Gun gun) {
  //  return false;
//}

void Player::add_points(int amount) {
    points+=amount;
}

void Player::add_health(int amount) {
    health+=amount;
}

bool Player::add_health_if_hass_less(int amount, int less_than) {
    if (health<less_than){
        health+=amount;
        return true;
    }
    return false;
}

