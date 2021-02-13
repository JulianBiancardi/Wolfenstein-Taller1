#include "game_caster.h"

#include <algorithm>

#include "../../../../../common/src/main/utils/angle.h"
#include "../../../../../common/src/main/utils/point.h"
#include "../../../../../common/src/main/utils/rectangle.h"
#include "../entities/object.h"
#include "../entities/player.h"
#include "ray_casting.h"
#include "sdl/image.h"

#define UNIT 3
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

GameCaster::GameCaster(Window& window, Map& map, unsigned int player_id)
    : renderer(window.get_renderer()),
      map(map),
      window(window),
      res_manager(window),
      player_id(player_id),
      hud(renderer) {}

GameCaster::~GameCaster() {}

void GameCaster::operator()() {
  draw_background();
  std::vector<double> wall_distances = draw_walls();
  draw_objects(wall_distances);
  hud.update(window, map.get_player(player_id));
  window.update();
}

void GameCaster::draw_background() {
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

std::vector<double> GameCaster::draw_walls() {
  std::vector<double> wall_collisions;
  wall_collisions.reserve(SCREEN_WIDTH);

  const Player& player = map.get_player(player_id);
  double ray_angle = player.get_angle() + FOV / 2;

  double angle_step = FOV / SCREEN_WIDTH;
  for (int i = 0; i < SCREEN_WIDTH;) {
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

void GameCaster::draw_objects(std::vector<double>& wall_distances) {
  std::vector<std::weak_ptr<Object>>& objects = map.get_drawables();

  std::vector<double> object_distances;
  printf("Drawing %d objects\n", objects.size());

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
  // TODO Optimize
  printf("ResID: %u\n", object.get_res_id());
  Image* image = object.get_image(res_manager);
  size_t img_width = image->get_width();
  size_t img_height = image->get_height();

  double x_relative =
      object.get_position().getX() - player.get_position().getX();
  // Y grows going down
  double y_relative =
      player.get_position().getY() - object.get_position().getY();

  double sprite_angle_rel = atan2(y_relative, x_relative);
  double sprite_angle = Angle::normalize(sprite_angle_rel - player.get_angle());

  // printf("sprite_angle_rel: %f\n", sprite_angle_rel);
  // printf("sprite_angle: %f\n", sprite_angle);
  // printf("player_angle: %f\n", player.get_angle());

  double projected_distance = distance * cos(sprite_angle);
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
