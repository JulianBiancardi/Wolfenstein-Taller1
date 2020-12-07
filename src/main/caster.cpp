#include "caster.h"

#include "ray_casting.h"
#include "sdl/image.h"
#include "utils/rectangle.h"

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

Caster::Caster(Window& window, Ray& player, Map& map)
    : renderer(window.get_renderer()),
      player(player),
      map(map),
      window(window),
      res_manager(window) {}

Caster::~Caster() {}

void Caster::operator()() {
  draw_background();
  draw_walls();
  window.update();
}

void Caster::draw_background() {
  window.fill(255, 255, 255, 255);

  window.set_draw_color(56, 56, 56, 255);
  SDL_Rect top_half;
  top_half.x = 0;
  top_half.y = 0;
  top_half.w = SCREEN_WIDTH;
  top_half.h = SCREEN_HEIGHT_HALF;
  SDL_RenderFillRect(renderer, &top_half);

  window.set_draw_color(112, 112, 112, 255);
  SDL_Rect bot_half;
  bot_half.x = 0;
  bot_half.y = SCREEN_HEIGHT_HALF;
  bot_half.w = SCREEN_WIDTH;
  bot_half.h = SCREEN_HEIGHT_HALF;
  SDL_RenderFillRect(renderer, &bot_half);
}

void Caster::draw_walls() {
  window.set_draw_color(0, 0, 0, 255);

  double ray_angle = player.get_angle() + FOV / 2;
  if (ray_angle > 2 * M_PI) {
    ray_angle -= 2 * M_PI;
  }
  double angle_step = FOV / SCREEN_WIDTH;

  for (int i = 0; i < SCREEN_WIDTH;) {
    Ray ray(player.get_origin(), ray_angle);

    bool y_intersection = true;
    Point intersection = RayCasting::get_intersection(map, ray, y_intersection);

    int wall_size = (int)WALL_SIZE *
                    RayCasting::get_scaling_factor(ray, player, intersection);

    Rectangle pos(SCREEN_HEIGHT_HALF - (wall_size / 2),
                  SCREEN_HEIGHT_HALF + (wall_size / 2), i, i + 1);

    Rectangle slice(0, 0, 0, 0);
    if (y_intersection == true) {
      slice = Rectangle(0, 64, std::fmod(intersection.getX(), 1) * 64,
                        (std::fmod(intersection.getX(), 1) * 64 + 1));
    } else {
      slice = Rectangle(0, 64, std::fmod(intersection.getY(), 1) * 64,
                        (std::fmod(intersection.getY(), 1) * 64 + 1));
    }

    Image* wall_img = res_manager.get_image(1);
    wall_img->draw(pos, &slice);
    /*
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
                     SCREEN_HEIGHT_HALF + (wall_size / 2));*/

    i++;
    ray_angle -= angle_step;
    if (ray_angle < 0) {
      ray_angle += 2 * M_PI;
    }
  }
}