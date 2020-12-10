#include <iostream>

#include "client/src/main/caster.h"
#include "client/src/main/ray_casting.h"
#include "client/src/main/sdl/window.h"
#include "common/src/main/utils/matrix.h"
#include "common/src/main/utils/ray.h"
#include "yaml-cpp/yaml.h"

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
void put_data(Matrix<int>& map_data);
Map load_map();

int main(int argc, char** argv) {
  /*
  Matrix<int> map_data(10, 10, 0);
  put_data(map_data);
  Map map(map_data);
  */

  Map map = load_map();

  Window window("Hello World!", SCREEN_WIDTH, SCREEN_HEIGHT);

  Ray player(1.5, 1.5, 0);

  Caster caster(window, player, map);
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
          caster();
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
    caster();
  }
}

/*
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
    map_data(3, 7) = CYAN_WALL;

    map_data(6, 5) = PINK_WALL;
}
*/

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

// TODO Move to MapReader
Map load_map() {
  YAML::Node yaml_file = YAML::LoadFile(
      "/home/julian/JULIAN/Taller1/Wolfenstein-Taller1/editor/src/main/build/"
      "new_map.yaml");

  size_t width = yaml_file["width"].as<int>();
  size_t height = yaml_file["height"].as<int>();
  Matrix<int> map_data(height, width, 0);

  const YAML::Node& objects = yaml_file["objects"];

  YAML::const_iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    const YAML::Node& object = *iter;

    int id = object["id"].as<int>();
    size_t x = object["x_position"].as<int>();
    size_t y = object["y_position"].as<int>();

    map_data(x, y) = id;
  }

  return Map(map_data);
}