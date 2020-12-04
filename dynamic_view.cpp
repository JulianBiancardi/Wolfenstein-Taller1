#include <iostream>

#include "src/main/matrix.h"
#include "src/main/ray.h"
#include "src/main/ray_casting.h"
#include "src/main/window.h"

#define UNIT 5
#define SCREEN_WIDTH (320 * UNIT)
#define SCREEN_HEIGHT (200 * UNIT)
#define SCREEN_WIDTH_HALF (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_HALF (SCREEN_HEIGHT / 2)

#define SCALING_FACTOR 1
#define CELL_SIZE 64
#define WALL_SIZE (SCALING_FACTOR * SCREEN_HEIGHT)
#define WALL 1
#define RED_WALL 2
#define GREEN_WALL 3
#define BLUE_WALL 4
#define YELLOW_WALL 5
#define CYAN_WALL 6
#define PINK_WALL 7
#define FOV_DEG 70
#define FOV (FOV_DEG * M_PI / 180)

void static handle_key_press(SDL_Keycode& key, Ray& player);
void print_map(Matrix<int>& map);
void put_data(Matrix<int>& map_data);
void draw_map(Matrix<int>& map_data, Matrix<int>& map);
void fill_cell(Matrix<int>& map, int i, int j, int data);

int main(int argc, char** argv) {
  Matrix<int> map_data(10, 10, 0);
  put_data(map_data);
  Map map(map_data);

  Window window("Hello World!", SCREEN_WIDTH, SCREEN_HEIGHT);

  Ray player(1.5, 1.5, 0);

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
      switch (map(intersection.getX(), intersection.getY())) {
        case WALL:
          window.set_draw_color(0, 0, 0, 255);
          break;
        case RED_WALL:
          window.set_draw_color(255, 0, 0, 255);
          break;
        case GREEN_WALL:
          window.set_draw_color(0, 255, 0, 255);
          break;
        case BLUE_WALL:
          window.set_draw_color(0, 0, 255, 255);
          break;
        case YELLOW_WALL:
          window.set_draw_color(255, 255, 0, 255);
          break;
        case CYAN_WALL:
          window.set_draw_color(0, 255, 255, 255);
          break;
        case PINK_WALL:
          window.set_draw_color(255, 0, 255, 255);
          break;
        default:
          break;
      }
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
  /*
    map_data(7, 2) = WALL;
    map_data(6, 2) = WALL;
    map_data(7, 3) = WALL;

    map_data(2, 6) = WALL;
    map_data(3, 6) = WALL;
    map_data(4, 6) = WALL;
    map_data(3, 5) = WALL;
    map_data(3, 7) = WALL;

    map_data(6, 5) = WALL;*/

  map_data(7, 2) = GREEN_WALL;
  map_data(6, 2) = BLUE_WALL;
  map_data(7, 3) = RED_WALL;

  map_data(2, 6) = YELLOW_WALL;
  map_data(3, 6) = BLUE_WALL;
  map_data(4, 6) = GREEN_WALL;
  map_data(3, 5) = RED_WALL;
  map_data(3, 7) = CYAN_WALL;

  map_data(6, 5) = PINK_WALL;
}

void static handle_key_press(SDL_Keycode& key, Ray& player) {
  double angle = player.get_angle();
  double cos_angle = cos(angle);
  double sin_angle = sin(angle);
  Point position = player.get_origin();
  double x = position.getX();
  double y = position.getY();
  switch (key) {
    case SDLK_w:
      printf("W\n");
      if (cos_angle > 0.9) {
        player.set_origin(x + 0.1, y);
      } else if (cos_angle < -0.9) {
        player.set_origin(x - 0.1, y);
      } else if (sin_angle > 0.9) {
        player.set_origin(x, y - 0.1);
      } else if (sin_angle < -0.9) {
        player.set_origin(x, y + 0.1);
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