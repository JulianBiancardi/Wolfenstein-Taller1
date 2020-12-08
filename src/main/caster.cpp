#include "caster.h"

#include <algorithm>

#include "ray_casting.h"
#include "sdl/image.h"
#include "utils/point.h"  // TODO Delete if not used in the file
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

// =======
bool static sprite_comp(_sprite& a, _sprite& b) {
  return a.get_distance() < b.get_distance();
}

void static load_sprites(std::vector<_sprite>& sprites);

void _sprite::update_distance(Point src) {
  distance = Point::distance(src, pos);
}
double _sprite::get_distance() { return distance; }
// =========

Caster::Caster(Window& window, Ray& player, Map& map)
    : renderer(window.get_renderer()),
      player(player),
      map(map),
      window(window),
      res_manager(window) {}

Caster::~Caster() {}

void Caster::operator()() {
  draw_background();
  std::vector<double> wall_distances = draw_walls();
  // draw_sprites(wall_distances);
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

std::vector<double> Caster::draw_walls() {
  std::vector<double> wall_collisions;
  wall_collisions.reserve(SCREEN_WIDTH);

  double ray_angle = player.get_angle() + FOV / 2;
  if (ray_angle > 2 * M_PI) {
    ray_angle -= 2 * M_PI;
  }

  double angle_step = FOV / SCREEN_WIDTH;
  for (int i = 0; i < SCREEN_WIDTH;) {
    Ray ray(player.get_origin(), ray_angle);

    Collision wall_collision = RayCasting::get_collision(map, ray);
    draw_wall(wall_collision, i, ray_angle);

    double projectected_dist = get_projected_distance(
        ray_angle, player.get_angle(), wall_collision.get_distance_from_src());
    wall_collisions.push_back(projectected_dist);

    i++;
    ray_angle -= angle_step;
    if (ray_angle < 0) {
      ray_angle += 2 * M_PI;
    }
  }

  return std::move(wall_collisions);
}

void Caster::draw_wall(Collision& collision, size_t screen_pos,
                       double ray_angle) {
  Image* image = res_manager.get_image(collision.get_collided_obj_id());

  double projected_distance = Caster::get_projected_distance(
      ray_angle, player.get_angle(), collision.get_distance_from_src());
  int wall_size = WALL_SIZE / projected_distance;

  Rectangle pos(SCREEN_HEIGHT_HALF - (wall_size / 2),
                SCREEN_HEIGHT_HALF + (wall_size / 2), screen_pos,
                screen_pos + 1);

  size_t img_width = image->get_width();
  size_t img_height = image->get_height();
  Rectangle slice(0, 0, 0, 0);
  if (collision.is_x_collision()) {
    double tmp;
    double y_offset = std::modf(collision.get_collision_point().getY(), &tmp);
    slice = Rectangle(0, img_height, y_offset * img_width,
                      y_offset * img_height + 1);
  } else {
    double tmp;
    double x_offset = std::modf(collision.get_collision_point().getX(), &tmp);
    slice = Rectangle(0, img_height, x_offset * img_width,
                      x_offset * img_height + 1);
  }

  image->draw(pos, &slice);
}

void Caster::draw_sprites(std::vector<double>& wall_distances) {
  std::vector<_sprite> sprites;
  load_sprites(sprites);
  sort_sprites(sprites);

  std::vector<_sprite>::iterator iter;
  for (iter = sprites.begin(); iter != sprites.end(); iter++) {
    double x_relative = (*iter).get_pos().getX() - player.get_origin().getX();
    double y_relative = (*iter).get_pos().getY() - player.get_origin().getY();
    double sprite_angle = atan2(y_relative, x_relative);
    double sprite_projected_distance =
        (*iter).get_distance() * cos(sprite_angle);
  }

  return;
}

double Caster::get_projected_distance(double ray_angle, double player_angle,
                                      double collision_distance) {
  double ray_offset = ray_angle - player_angle;
  return collision_distance * cos(ray_offset);
}

// TODO Delete when linked with map.
void static load_sprites(std::vector<_sprite>& sprites) {
  sprites.push_back(_sprite(Point(1.5, 3.5)));
  sprites.push_back(_sprite(Point(5, 1.5)));
  sprites.push_back(_sprite(Point(1.5, 1.5)));
}

void Caster::sort_sprites(std::vector<_sprite>& sprites) {
  std::vector<_sprite>::iterator iter;
  for (iter = sprites.begin(); iter != sprites.end(); iter++) {
    (*iter).update_distance(player.get_origin());
  }
  std::sort(sprites.begin(), sprites.end(), sprite_comp);
}
