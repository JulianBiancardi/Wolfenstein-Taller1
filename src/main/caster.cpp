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
  std::vector<Collision> wall_collisions = get_wall_collisions();
  draw(wall_collisions);
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

std::vector<Collision> Caster::get_wall_collisions() {
  std::vector<Collision> wall_collisions;
  wall_collisions.reserve(SCREEN_WIDTH);

  double ray_angle = player.get_angle() + FOV / 2;
  if (ray_angle > 2 * M_PI) {
    ray_angle -= 2 * M_PI;
  }

  double angle_step = FOV / SCREEN_WIDTH;
  for (int i = 0; i < SCREEN_WIDTH;) {
    Ray ray(player.get_origin(), ray_angle);
    wall_collisions.push_back(RayCasting::get_collision(map, ray));

    i++;
    ray_angle -= angle_step;
    if (ray_angle < 0) {
      ray_angle += 2 * M_PI;
    }
  }

  return std::move(wall_collisions);
}

void Caster::draw(std::vector<Collision> wall_collisions) {
  double ray_angle = player.get_angle() + FOV / 2;
  if (ray_angle > 2 * M_PI) {
    ray_angle -= 2 * M_PI;
  }

  double angle_step = FOV / SCREEN_WIDTH;
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    Collision collision = wall_collisions[i];
    Image* image = res_manager.get_image(collision.get_collided_obj_id());

    double projected_distance = Caster::get_projected_distance(
        ray_angle, player.get_angle(), collision.get_distance_from_src());
    int wall_size = WALL_SIZE / projected_distance;

    Rectangle pos(SCREEN_HEIGHT_HALF - (wall_size / 2),
                  SCREEN_HEIGHT_HALF + (wall_size / 2), i, i + 1);

    Rectangle slice(0, 0, 0, 0);
    if (collision.is_x_collision()) {
      // TODO Beautify
      slice = Rectangle(0, image->get_height(),
                        std::fmod(collision.get_collision_point().getY(), 1) *
                            image->get_width(),
                        (std::fmod(collision.get_collision_point().getY(), 1) *
                             image->get_height() +
                         1));
    } else {
      slice = Rectangle(0, image->get_height(),
                        std::fmod(collision.get_collision_point().getX(), 1) *
                            image->get_width(),
                        (std::fmod(collision.get_collision_point().getX(), 1) *
                             image->get_height() +
                         1));
    }

    image->draw(pos, &slice);

    ray_angle -= angle_step;
    if (ray_angle < 0) {
      ray_angle += 2 * M_PI;
    }
  }
}

double Caster::get_projected_distance(double ray_angle, double player_angle,
                                      double collision_distance) {
  double ray_offset = ray_angle - player_angle;
  return collision_distance * cos(ray_offset);
}