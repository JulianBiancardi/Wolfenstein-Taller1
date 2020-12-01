#include "player.h"

void move_from_current_position_if_can(int x, int y){
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
