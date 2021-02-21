#include "game_caster.h"

#include <algorithm>

#include "../../../../../common/src/main/utils/angle.h"
#include "../../../../../common/src/main/utils/point.h"
#include "../entities/object.h"
#include "../entities/player.h"
#include "ray_casting.h"
#include "sdl/image.h"

#define SCALING_FACTOR 70
#define FOV_DEG 70
#define FOV (FOV_DEG * M_PI / 180)

/* Receives an angle and returns where it should be on screen,
 * where 0 is the left-most of the screen and 1 the right-most edge.
 */
double static fov_scale(double angle) {
  if (angle > M_PI) {
    angle -= 2 * M_PI;
  }
  return (-1.0 / FOV) * angle + 0.5;
}

GameCaster::GameCaster(Window& window, Map& map, unsigned int player_id)
    : renderer(window.get_renderer()),
      map(map),
      window(window),
      res_manager(window),
      player_id(player_id),
      hud(window, res_manager) {}

GameCaster::~GameCaster() {}

void GameCaster::operator()() {
  draw_background();
  std::vector<double> wall_distances = draw_walls();
  draw_objects(wall_distances);
  hud.update(map.get_player(player_id));
  window.update();
}

void GameCaster::draw_background() {
  window.fill(255, 255, 255, 255);

  window.set_draw_color(56, 56, 56, 255);
  SDL_Rect top_half;
  top_half.x = 0;
  top_half.y = 0;
  top_half.w = window.get_width();
  top_half.h = window.get_height() / 2;
  SDL_RenderFillRect(renderer, &top_half);

  window.set_draw_color(112, 112, 112, 255);
  SDL_Rect bot_half;
  bot_half.x = 0;
  bot_half.y = window.get_height() / 2;
  bot_half.w = window.get_width();
  bot_half.h = window.get_height() / 2;
  SDL_RenderFillRect(renderer, &bot_half);
}

std::vector<double> GameCaster::draw_walls() {
  std::vector<double> wall_collisions;
  wall_collisions.reserve(window.get_width());

  const Player& player = map.get_player(player_id);
  double ray_angle = player.get_angle() + FOV / 2;

  double angle_step = FOV / window.get_width();
  for (int i = 0; i < window.get_width();) {
    Ray ray(player.get_position(), ray_angle);

    Collision wall_collision = RayCasting::get_collision(map, ray);
    draw_wall(wall_collision, i, ray_angle);

    double projectected_dist = get_projected_distance(
        ray_angle, player.get_angle(), wall_collision.get_distance_from_src());
    wall_collisions.push_back(projectected_dist);

    i++;
    ray_angle -= angle_step;
  }

  return std::move(wall_collisions);
}

void GameCaster::draw_wall(Collision& collision, size_t screen_pos,
                           double ray_angle) {
  Image* image = res_manager.get_image(collision.get_collided_obj_id());

  double projected_distance = GameCaster::get_projected_distance(
      ray_angle, map.get_player(player_id).get_angle(),
      collision.get_distance_from_src());
  int wall_size = (SCALING_FACTOR * window.get_height()) /
                  (projected_distance * image->get_height());

  size_t img_width = image->get_width();
  size_t img_height = image->get_height();
  int line = 0;
  if (collision.is_x_collision()) {
    double tmp;
    double y_offset = std::modf(collision.get_collision_point().getY(), &tmp);
    line = y_offset * img_width;
  } else {
    double tmp;
    double x_offset = std::modf(collision.get_collision_point().getX(), &tmp);
    line = x_offset * img_width;
  }

  SDL_Rect pos = {(int)screen_pos, (window.get_height() / 2) - (wall_size / 2),
                  1, wall_size};
  SDL_Rect slice = {line, 0, 1, (int)img_height};
  image->draw(&pos, &slice);
}

void GameCaster::draw_objects(std::vector<double>& wall_distances) {
  std::vector<std::weak_ptr<Object>>& objects = map.get_drawables();

  std::vector<double> object_distances;

  clean_objects(objects);
  sort_objects(objects, object_distances);

  for (int i = 0; i < objects.size(); i++) {
    draw_object(*objects[i].lock(), object_distances[i], wall_distances);
  }
}

void GameCaster::draw_object(Object& object, double distance,
                             std::vector<double>& wall_distances) {
  if (distance == 0) {  // Object is oneself
    return;
  }

  const Player& player = map.get_player(player_id);
  double player_angle = player.get_angle();
  // TODO Optimize
  Image* image = object.get_image(res_manager);
  SDL_Rect* slice = object.get_slice(&player_angle);
  size_t img_width = slice->w;
  size_t img_height = slice->h;

  double x_relative =
      object.get_position().getX() - player.get_position().getX();
  // Y grows going down
  double y_relative =
      player.get_position().getY() - object.get_position().getY();

  double sprite_angle_rel = atan2(y_relative, x_relative);
  double sprite_angle = Angle::normalize(sprite_angle_rel - player.get_angle());

  double projected_distance = distance * cos(sprite_angle);
  int sprite_size =
      (SCALING_FACTOR * window.get_height()) / (projected_distance * img_width);

  int x = fov_scale(sprite_angle) * window.get_width();
  if (x > window.get_width() * 1.2 || x < -0.2 * window.get_width()) return;
  int x0 = x - (sprite_size / 2) - 1;

  for (int i = 0; i < sprite_size; i++) {
    x0 = x0 + 1;
    if (x0 < 0) {
      continue;
    }
    if (x0 > window.get_width()) {
      break;
    }
    if (wall_distances[x0] < projected_distance) {
      continue;
    }

    SDL_Rect pos = {x0, (window.get_height() / 2) - (sprite_size / 2), 1,
                    sprite_size};
    SDL_Rect* slice = object.get_slice(&player_angle);
    slice->x += (int)(i * img_width) / sprite_size;
    slice->w = 1;

    image->draw(&pos, slice);
  }
}

double GameCaster::get_projected_distance(double ray_angle, double player_angle,
                                          double collision_distance) {
  double ray_offset = ray_angle - player_angle;
  return collision_distance * cos(ray_offset);
}

void GameCaster::clean_objects(std::vector<std::weak_ptr<Object>>& objects) {
  std::vector<std::weak_ptr<Object>> objects_kept;

  std::vector<std::weak_ptr<Object>>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    if (!iter->expired()) {
      objects_kept.push_back(*iter);
    }
  }

  std::swap(objects_kept, objects);
}

void GameCaster::sort_objects(std::vector<std::weak_ptr<Object>>& objects,
                              std::vector<double>& distances) {
  Point player_pos = map.get_player(player_id).get_position();
  size_t size = objects.size();

  distances.resize(size);

  for (size_t i = 0; i < size; i++) {
    distances[i] = objects[i].lock()->get_position().distance_from(player_pos);
  }

  /* Insertion sort is used since it is the best algorithm for nearly-sorted
   * arrays. The changes between iteration and iteration are too small,
   * so it is always nearly sorted. Best case: O(n).
   */
  for (size_t i = 1; i < size; i++) {
    for (size_t j = i; j > 0 && distances[j - 1] <= distances[j]; j--) {
      std::swap(distances[j], distances[j - 1]);
      std::swap(objects[j], objects[j - 1]);
    }
  }
}
