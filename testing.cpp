#include <iostream>

#include "src/main/matrix.h"
#include "src/main/ray.h"
#include "src/main/ray_casting.h"
#include "src/main/window.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_WIDTH_HALF (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_HALF (SCREEN_HEIGHT / 2)

#define CELL_SIZE 64
#define WALL_SIZE 20000
#define WALL 1
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
  bool run = true;
  while (run) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          run = false;
          break;
        case SDL_KEYDOWN:
          printf("Key press\n");
          handle_key_press(event.key.keysym.sym, player);
          break;
        case SDL_KEYUP:
          printf("Key release\n");
          break;
        case SDL_MOUSEBUTTONDOWN:
          printf("Mouse clicked\n");
          break;
        case SDL_MOUSEBUTTONUP:
          printf("Mouse unclicked\n");
          break;
        default:
          break;
      }
    }

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

      // std::cout << "(" << intersection.getX() << "," << intersection.getY()
      //          << ")" << std::endl;

      int wall_size = (int)WALL_SIZE *
                      RayCasting::get_scaling_factor(ray, player, intersection);

      window.draw_line(i, SCREEN_HEIGHT_HALF - (wall_size / 2), i,
                       SCREEN_HEIGHT_HALF + (wall_size / 2));

      i++;
      ray_angle -= angle_step;
      if (ray_angle < 0) {
        ray_angle += 2 * M_PI;
      }
    }

    window.update();
  }
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

void static handle_key_press(SDL_Keycode& key, Ray& player) {
  double angle = player.get_angle();
  double cos_angle = cos(angle);
  double sin_angle = sin(angle);
  Point position = player.get_origin();
  int x = position.getX();
  int y = position.getY();
  switch (key) {
    case SDLK_w:
      printf("W\n");
      if (cos_angle > 0.9) {
        player.set_origin(x + 5, y);
      } else if (cos_angle < -0.9) {
        player.set_origin(x - 5, y);
      } else if (sin_angle > 0.9) {
        player.set_origin(x, y - 5);
      } else if (sin_angle < -0.9) {
        player.set_origin(x, y + 5);
      }
      break;
    case SDLK_s:
      printf("S\n");
      break;
    case SDLK_a:
      printf("A\n");
      angle += 0.1;
      if (angle >= 2 * M_PI) {
        angle -= 2 * M_PI;
      }
      player.set_angle(angle);
      break;
    case SDLK_d:
      printf("D\n");
      angle -= 0.1;
      if (angle < 0) {
        angle += 2 * M_PI;
      }
      player.set_angle(angle);
      break;
    default:
      break;
  }
}