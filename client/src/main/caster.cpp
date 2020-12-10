#include "caster.h"

#include <algorithm>

#include "../../../common/src/main/utils/point.h"  // TODO Delete if not used in the file
#include "../../../common/src/main/utils/rectangle.h"
#include "ray_casting.h"
#include "sdl/image.h"

#define UNIT 5
#define SCREEN_WIDTH (320 * UNIT)
#define SCREEN_HEIGHT (200 * UNIT)
#define SCREEN_WIDTH_HALF (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_HALF (SCREEN_HEIGHT / 2)

#define SCALING_FACTOR (64 * SCREEN_HEIGHT)
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
  return a.get_distance() > b.get_distance();
}

void static load_sprites(std::vector<_sprite>& sprites);

void _sprite::update_distance(Point src) {
  distance = Point::distance(src, pos);
}
double _sprite::get_distance() { return distance; }
int _sprite::get_id() { return id; }
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
  draw_sprites(wall_distances);
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
  int wall_size = SCALING_FACTOR / (projected_distance * image->get_height());

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
    draw_sprite(*iter, wall_distances);
  }
}

void Caster::draw_sprite(_sprite& sprite, std::vector<double>& wall_distances) {
  // TODO Optimize
  Image* image = res_manager.get_image(sprite.get_id());
  size_t img_width = image->get_width();
  size_t img_height = image->get_height();

  double x_relative = sprite.get_pos().getX() - player.get_origin().getX();
  // Y grows going down
  double y_relative = player.get_origin().getY() - sprite.get_pos().getY();

  double sprite_angle_rel = atan2(y_relative, x_relative);
  /*if (sprite_angle_rel > 2 * M_PI) {
    sprite_angle_rel -= 2 * M_PI;
  } else if (sprite_angle_rel < 0) {
    sprite_angle_rel += 2 * M_PI;
  }*/
  double sprite_angle = sprite_angle_rel - player.get_angle();
  if (sprite_angle > 2 * M_PI) {
    sprite_angle -= 2 * M_PI;
  } else if (sprite_angle < 0) {
    sprite_angle += 2 * M_PI;
  }

  // printf("sprite_angle_rel: %f\n", sprite_angle_rel);
  // printf("sprite_angle: %f\n", sprite_angle);
  // printf("player_angle: %f\n", player.get_angle());

  double projected_distance = sprite.get_distance() * cos(sprite_angle);
  // printf("proj_dist: %f\n", projected_distance);
  int sprite_size = SCALING_FACTOR / (projected_distance * img_height);
  // printf("sprite_size: %d\n", sprite_size);

  int x = sin(sprite_angle) * (-SCREEN_WIDTH) + SCREEN_WIDTH_HALF;
  // TODO Move to constants
  if (x > SCREEN_WIDTH * 1.2 || x < -0.2 * SCREEN_WIDTH) return;
  // printf("center: %d\n", x);
  int x0 = x - sprite_size / 2 - 1;
  // printf("x0: %d\n", x0);

  for (int i = 0; i < sprite_size; i++) {
    x0 = x0 + 1;
    if (x0 < 0) {
      continue;
    }
    if (x0 > SCREEN_WIDTH) {
      break;
    }
    if (wall_distances[x0] < projected_distance) {
      continue;
    }

    Rectangle pos(SCREEN_HEIGHT_HALF - sprite_size / 2,
                  SCREEN_HEIGHT_HALF + sprite_size / 2, x0, x0 + 1);
    Rectangle slice(0, sprite_size, (i * img_width) / sprite_size,
                    ((i * img_width) / sprite_size) + 1);
    image->draw(pos, &slice);
  }
}

double Caster::get_projected_distance(double ray_angle, double player_angle,
                                      double collision_distance) {
  double ray_offset = ray_angle - player_angle;
  return collision_distance * cos(ray_offset);
}

// TODO Delete when linked with map.
void static load_sprites(std::vector<_sprite>& sprites) {
  sprites.push_back(_sprite(Point(1.5, 3.5), 14));
  sprites.push_back(_sprite(Point(5, 1.5), 14));
  sprites.push_back(_sprite(Point(1.5, 1.5), 14));
}

void Caster::sort_sprites(std::vector<_sprite>& sprites) {
  std::vector<_sprite>::iterator iter;
  for (iter = sprites.begin(); iter != sprites.end(); iter++) {
    (*iter).update_distance(player.get_origin());
  }
  std::sort(sprites.begin(), sprites.end(), sprite_comp);
}
