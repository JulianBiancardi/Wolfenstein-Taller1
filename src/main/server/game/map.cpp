#include <iostream>

#include "map.h"

#define CELL_SIZE 64
#define WALL 1

void fill_cell(Matrix<int>& map, int i, int j, int data) {
  for (int x = CELL_SIZE * i; x < CELL_SIZE * i + CELL_SIZE; x++) {
    for (int y = CELL_SIZE * j; y < CELL_SIZE * j + CELL_SIZE; y++) {
      map(x, y) = data;
    }
  }
}

void put_data(Matrix<int>& map_data) {
  for (int i = 0; i < map_data.get_columns(); i++) {
    map_data(i, 0) = WALL;  // TOP
    map_data(0, i) = WALL;  // LEFT
    map_data(i, 9) = WALL;  // BOT
    map_data(9, i) = WALL;  // RIGHT
  }
}

void draw_map(Matrix<int>& map_data, Matrix<int>& map) {
  for (int i = 0; i < map_data.get_columns(); i++) {
    for (int j = 0; j < map_data.get_rows(); j++) {
      int data = map_data(i, j);
      fill_cell(map, i, j, data);
    }
  }
}

void print_map(Matrix<int>& map) {
  for (int i = 0; i < map.get_columns(); i++) {
    for (int j = 0; j < map.get_rows(); j++) {
      std::cout << map(i, j);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

Map::Map() : expanded_map(640,640,0){
  Matrix<int> map_data(10, 10, 0); // Emulates map loaded
  put_data(map_data);
  print_map(map_data);
  draw_map(map_data, expanded_map);
}

bool Map::can_move_to(Point destiny){
  if(expanded_map(destiny.getX(),destiny.getY()) == WALL)
  	return false;

  return true;
}

Map& Map::get_map(){
  static Map map;
  return map;
}
