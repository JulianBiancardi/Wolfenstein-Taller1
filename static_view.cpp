#include <iostream>

#include "src/main/matrix.h"
#include "src/main/ray.h"
#include "src/main/ray_casting.h"
#include "src/main/window.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH_HALF (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_HALF (SCREEN_HEIGHT / 2)

#define CELL_SIZE 64
#define WALL_SIZE 20000
#define WALL 1
#define RED_WALL 2
#define GREEN_WALL 3
#define BLUE_WALL 4
#define YELLOW_WALL 5
#define FOV 1.04

void static handle_key_press(SDL_Keycode& key, Ray& player);
void print_map(Matrix<int>& map);
void put_data(Matrix<int>& map_data);
void draw_map(Matrix<int>& map_data, Matrix<int>& map);
void fill_cell(Matrix<int>& map, int i, int j, int data);

int main(int argc, char** argv) {
  Matrix<int> map_data(10, 10, 0);
  put_data(map_data);
  print_map(map_data);
  Matrix<int> map(640, 640, 0);
  draw_map(map_data, map);

  Window window("Hello World!", SCREEN_WIDTH, SCREEN_HEIGHT);

  Ray player(100, 100, 0);

  SDL_Event event;

  window.fill(255, 255, 255, 255);
  window.set_draw_color(0, 0, 0, 255);

  double ray_angle = player.get_angle() + FOV / 2;
  if (ray_angle > 2 * M_PI) {
    ray_angle -= 2 * M_PI;
  }
  double angle_step = FOV / SCREEN_WIDTH;
  for (int i = 0; i < SCREEN_WIDTH;) {
    Ray ray(player.get_origin(), ray_angle);

    Point intersection = RayCasting::get_intersection(map, ray);
    // std::cout << "ANGLE: " << ray.get_angle() << " ";
    // std::cout << "(" << intersection.getX() << "," << intersection.getY() <<
    // ")"
    //          << std::endl;

    int wall_size = (int)WALL_SIZE *
                    RayCasting::get_scaling_factor(ray, player, intersection);
    /*switch (map(intersection.getX(), intersection.getY())) {
      case 1:
        window.set_draw_color(0, 0, 0, 255);
        break;
      case 2:
        window.set_draw_color(255, 0, 0, 255);
        break;
      case 3:
        window.set_draw_color(0, 255, 0, 255);
        break;
      case 4:
        window.set_draw_color(0, 0, 255, 255);
        break;
      case 5:
        window.set_draw_color(0, 255, 255, 255);
        break;
      default:
        break;
    }*/
    window.draw_line(i, SCREEN_HEIGHT_HALF - (wall_size / 2), i,
                     SCREEN_HEIGHT_HALF + (wall_size / 2));

    i++;
    ray_angle -= angle_step;
    if (ray_angle < 0) {
      ray_angle += 2 * M_PI;
    }
  }

  window.update();
  printf("%d", map((int)576.99, (int)99.7));
  SDL_Delay(5000);
}

void put_data(Matrix<int>& map_data) {
  for (int i = 0; i < map_data.get_columns(); i++) {
    map_data(i, 0) = WALL;  // TOP
    map_data(0, i) = WALL;  // LEFT
    map_data(i, 9) = WALL;  // BOT
    map_data(9, i) = WALL;  // RIGHT
  }

  map_data(7, 2) = WALL;
  map_data(6, 2) = WALL;
  map_data(7, 3) = WALL;

  map_data(2, 6) = WALL;
  map_data(3, 6) = WALL;
  map_data(4, 6) = WALL;
  map_data(3, 5) = WALL;
  map_data(3, 7) = WALL;

  map_data(6, 5) = WALL;
  /*
  map_data(7, 2) = GREEN_WALL;
  map_data(6, 2) = BLUE_WALL;
  map_data(7, 3) = RED_WALL;

  map_data(2, 6) = YELLOW_WALL;
  map_data(3, 6) = BLUE_WALL;
  map_data(4, 6) = GREEN_WALL;
  map_data(3, 5) = RED_WALL;
  map_data(3, 7) = GREEN_WALL;

  map_data(6, 5) = BLUE_WALL;
  */
}

void draw_map(Matrix<int>& map_data, Matrix<int>& map) {
  for (int i = 0; i < map_data.get_columns(); i++) {
    for (int j = 0; j < map_data.get_rows(); j++) {
      int data = map_data(i, j);
      fill_cell(map, i, j, data);
    }
  }
}

void fill_cell(Matrix<int>& map, int i, int j, int data) {
  for (int x = CELL_SIZE * i; x < CELL_SIZE * i + CELL_SIZE; x++) {
    for (int y = CELL_SIZE * j; y < CELL_SIZE * j + CELL_SIZE; y++) {
      map(x, y) = data;
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
