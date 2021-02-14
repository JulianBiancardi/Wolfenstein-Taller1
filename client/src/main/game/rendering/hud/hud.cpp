#include "hud.h"

#include "../../../../../../common/src/main/ids/gun_ids.h"
#include "../sdl/image.h"
#include "../sdl/text.h"

#define FONT_PATH "../../res/fonts/wolfenstein.ttf"
#define BACKGROUND_PATH "../../res/images/hud/IMG_HUD_Background.png"
#define BJ_FACES_PATH "../../res/images/hud/IMG_HUD_BJFaces.png"
#define KEY_PATH "../../res/images/hud/IMG_HUD_Key1.png"
#define NUMBER_PATH "../../res/images/hud/IMG_HUD_Numbers.png"

#define PREFEER_WIDTH 320
#define PREFEER_HEIGHT 200

#define PIXEL 1
// Number 8x16

#define STATS_Y_POS 16

#define LEVEL_X_POS 20
#define POINTS_X_POS 88
#define LIVES_X_POS 112
#define FACE_X_POS 136
#define HEALTH_X_POS 184
#define BULLETS_X_POS 226
#define KEY_X_POS 240
#define GUN_X_POS 256

#define NUMBER_FRAME_X_COUNT 10
#define FACE_FRAME_X_COUNT 3
#define FACE_FRAME_Y_COUNT 7

Hud::Hud(SDL_Renderer* renderer)
    : renderer(renderer),
      background(renderer, BACKGROUND_PATH),
      bj_faces(renderer, BJ_FACES_PATH),
      key(renderer, KEY_PATH),
      numbers(renderer, NUMBER_PATH) {
  number_frame_w = (numbers.get_width() - 2 * PIXEL) / NUMBER_FRAME_X_COUNT;
  number_frame_h = numbers.get_height();

  size_t font_size = 12;
  font = TTF_OpenFont(FONT_PATH, font_size);
}

Hud::~Hud() {}

void Hud::update(const Window& window, const Player& player) {
  // TODO MOVE TO CONFIG
  // TODO Move to ResourceManager since this is wasting resources

  // Get the scale factor
  scale_x = window.get_width() / PREFEER_WIDTH;
  scale_y = window.get_height() / PREFEER_HEIGHT;

  _show_background(window);
  _show_stats(window, player);
  _show_lives(window, player);
  _show_points(window, player);
  _show_health(window, player);
  _show_bullets(window, player);
  _show_face(window, player);
  _show_key(window, player);
  _show_gun(window, player);
}

void Hud::_show_background(const Window& window) {
  SDL_Rect rect_pos;
  rect_pos.x = 0;
  rect_pos.y = window.get_height() - (background.get_height() * scale_y);
  rect_pos.w = background.get_width() * scale_x;
  rect_pos.h = background.get_height() * scale_y;
  background.draw(&rect_pos, nullptr);
}

void Hud::_show_stats(const Window& window, const Player& player) {
  /*
    rect_pos.x = LEVEL_X_POS * scale_x;
    Text level(renderer, "1", font, white, &rect_pos);

    rect_pos.x = POINTS_X_POS * scale_x;
    Text points(renderer, std::to_string(player.get_points()), font, white,
                &rect_pos);

    rect_pos.x = LIVES_X_POS * scale_x;
    Text lives(renderer, std::to_string(player.get_lives()), font, white,
               &rect_pos);

    rect_pos.x = HEALTH_X_POS * scale_x;
    Text health(renderer, std::to_string(player.get_percentage_health()),
    font, white, &rect_pos);

    rect_pos.x = BULLETS_X_POS * scale_x;
    Text bullets(renderer, std::to_string(player.get_bullets()), font,
    white, &rect_pos);*/
}

void Hud::_show_lives(const Window& window, const Player& player) {
  int lives = player.get_lives();

  int unidades = lives;

  SDL_Rect rect_pos;
  rect_pos.x = LIVES_X_POS * scale_x;
  rect_pos.y = window.get_height() -
               ((background.get_height() - STATS_Y_POS * PIXEL) * scale_y);
  rect_pos.w = number_frame_w * scale_x;
  rect_pos.h = number_frame_h * scale_y;

  rect_pos.x = LIVES_X_POS * scale_x;
  _show_number(unidades, &rect_pos);
}

void Hud::_show_points(const Window& window, const Player& player) {
  int points = player.get_points();

  int millares = points / 1000;
  int centenas = (points - (millares * 1000)) / 100;
  int decenas = (points - (millares * 1000 + centenas * 100)) / 10;
  int unidades = points - (millares * 1000 + centenas * 100 + decenas * 10);

  SDL_Rect rect_pos;
  rect_pos.x = POINTS_X_POS * scale_x;
  rect_pos.y = window.get_height() -
               ((background.get_height() - STATS_Y_POS * PIXEL) * scale_y);
  rect_pos.w = number_frame_w * scale_x;
  rect_pos.h = number_frame_h * scale_y;

  rect_pos.x = POINTS_X_POS * scale_x;
  _show_number(unidades, &rect_pos);

  rect_pos.x = (POINTS_X_POS - 1 * (number_frame_w + PIXEL)) * scale_x;
  _show_number(decenas, &rect_pos);

  rect_pos.x = (POINTS_X_POS - 2 * (number_frame_w + PIXEL)) * scale_x;
  _show_number(centenas, &rect_pos);

  rect_pos.x = (POINTS_X_POS - 3 * (number_frame_w + PIXEL)) * scale_x;
  _show_number(millares, &rect_pos);
}

void Hud::_show_health(const Window& window, const Player& player) {
  int health = player.get_percentage_health();

  int centenas = health / 100;
  int decenas = (health - (centenas * 100)) / 10;
  int unidades = health - (centenas * 100 + decenas * 10);

  SDL_Rect rect_pos;
  rect_pos.x = HEALTH_X_POS * scale_x;
  rect_pos.y = window.get_height() -
               ((background.get_height() - STATS_Y_POS * PIXEL) * scale_y);
  rect_pos.w = number_frame_w * scale_x;
  rect_pos.h = number_frame_h * scale_y;

  rect_pos.x = HEALTH_X_POS * scale_x;
  _show_number(unidades, &rect_pos);

  rect_pos.x = (HEALTH_X_POS - 1 * (number_frame_w + PIXEL)) * scale_x;
  _show_number(decenas, &rect_pos);

  rect_pos.x = (HEALTH_X_POS - 2 * (number_frame_w + PIXEL)) * scale_x;
  _show_number(centenas, &rect_pos);
}

void Hud::_show_bullets(const Window& window, const Player& player) {
  int bullets = player.get_bullets();

  int centenas = bullets / 100;
  int decenas = (bullets - (centenas * 100)) / 10;
  int unidades = bullets - (centenas * 100 + decenas * 10);

  SDL_Rect rect_pos;
  rect_pos.x = BULLETS_X_POS * scale_x;
  rect_pos.y = window.get_height() -
               ((background.get_height() - STATS_Y_POS * PIXEL) * scale_y);
  rect_pos.w = number_frame_w * scale_x;
  rect_pos.h = number_frame_h * scale_y;

  rect_pos.x = BULLETS_X_POS * scale_x;
  _show_number(unidades, &rect_pos);

  rect_pos.x = (BULLETS_X_POS - 1 * (number_frame_w + PIXEL)) * scale_x;
  _show_number(decenas, &rect_pos);

  rect_pos.x = (BULLETS_X_POS - 2 * (number_frame_w + PIXEL)) * scale_x;
  _show_number(centenas, &rect_pos);
}

void Hud::_show_number(int number, SDL_Rect* position) {
  int sprite_x = number % NUMBER_FRAME_X_COUNT;
  SDL_Rect rect_slice = {(sprite_x * (number_frame_w + PIXEL)), 0,
                         number_frame_w, number_frame_h};
  numbers.draw(position, &rect_slice);
}

void Hud::_show_face(const Window& window, const Player& player) {
  int frame_width = (bj_faces.get_width() - 2 * PIXEL) / FACE_FRAME_X_COUNT;
  int frame_height =
      (bj_faces.get_height() - 7 * PIXEL) / (FACE_FRAME_Y_COUNT + 1);
  size_t health = player.get_percentage_health();

  Uint32 ticks = SDL_GetTicks();
  Uint32 seconds = ticks / 1000;
  Uint32 sprite_x = seconds % FACE_FRAME_X_COUNT;
  Uint32 sprite_y =
      ((100 - health) / (FACE_FRAME_Y_COUNT * 2)) % FACE_FRAME_Y_COUNT;

  SDL_Rect rect_face;
  rect_face.x = FACE_X_POS * scale_x;
  rect_face.y =
      window.get_height() - ((background.get_height() - 4 * PIXEL) * scale_y);
  rect_face.w = frame_width * scale_x;
  rect_face.h = frame_height * scale_y;

  SDL_Rect rect_slice = {(sprite_x * (frame_width + PIXEL)),
                         (sprite_y * (frame_height + PIXEL)), frame_width,
                         frame_height};
  bj_faces.draw(&rect_face, &rect_slice);
}

void Hud::_show_key(const Window& window, const Player& player) {
  if (player.has_key()) {
    SDL_Rect rect_key;
    rect_key.x = KEY_X_POS * scale_x;
    rect_key.y =
        window.get_height() - ((background.get_height() - 4 * PIXEL) * scale_y);
    rect_key.w = key.get_width() * scale_x;
    rect_key.h = key.get_height() * scale_y;
    key.draw(&rect_key, nullptr);
  }
}

void Hud::_show_gun(const Window& window, const Player& player) {
  std::string gun_image_path;
  switch (player.get_gun()) {
    case KNIFE_ID:
      gun_image_path = "../../res/images/hud/IMG_HUD_Knife.png";
      break;
    case PISTOL_ID:
      gun_image_path = "../../res/images/hud/IMG_HUD_Pistol.png";
      break;
    case CHAIN_CANNON_ID:
      gun_image_path = "../../res/images/hud/IMG_HUD_ChainCanon.png";
      break;
    case MACHINE_GUN_ID:
      gun_image_path = "../../res/images/hud/IMG_HUD_MachineGun.png";
      break;
    case ROCKET_LAUNCHER_ID:
      gun_image_path = "../../res/images/hud/IMG_HUD_RocketLauncher.png";
      break;
    default:
      return;
  }

  Image gun(renderer, gun_image_path);
  SDL_Rect rect_gun;
  rect_gun.x = GUN_X_POS * scale_x;
  rect_gun.y =
      window.get_height() - ((background.get_height() - 8 * PIXEL) * scale_y);
  rect_gun.w = gun.get_width() * scale_x;
  rect_gun.h = gun.get_height() * scale_y;

  gun.draw(&rect_gun, nullptr);
}