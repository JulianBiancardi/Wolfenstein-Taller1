#include "hud.h"

#include <string>

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

Hud::Hud(SDL_Renderer* renderer, const Window& window)
    : renderer(renderer),
      window(window),
      scale_x(window.get_width() / PREFEER_WIDTH),
      scale_y(window.get_height() / PREFEER_HEIGHT),
      background(renderer, BACKGROUND_PATH),
      bj_faces(renderer, BJ_FACES_PATH),
      key(renderer, KEY_PATH),
      numbers(renderer, NUMBER_PATH) {
  number_frame_w = (numbers.get_width() - 9 * PIXEL) / NUMBER_FRAME_X_COUNT;
  number_frame_h = numbers.get_height();

  size_t font_size = 12;
  font = TTF_OpenFont(FONT_PATH, font_size);
}

Hud::~Hud() {}

void Hud::update(const Player& player) {
  // TODO MOVE TO CONFIG
  // TODO Move to ResourceManager since this is wasting resources
  _show_background();
  _show_lives(player);
  _show_points(player);
  _show_health(player);
  _show_bullets(player);
  _show_face(player);
  _show_key(player);
  _show_gun(player);
  _show_player_gun(player);
}

void Hud::_show_background() {
  SDL_Rect rect_pos;
  rect_pos.x = 0;
  rect_pos.y = window.get_height() - (background.get_height() * scale_y);
  rect_pos.w = background.get_width() * scale_x;
  rect_pos.h = background.get_height() * scale_y;
  background.draw(&rect_pos, nullptr);
}

void Hud::_show_lives(const Player& player) {
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

void Hud::_show_points(const Player& player) {
  int points = player.get_points();

  int cent_mil = points / 100000;
  int dec_mil = (points - (cent_mil * 100000)) / 10000;
  int mil = (points - (cent_mil * 100000 + dec_mil * 10000)) / 1000;
  int centenas =
      (points - (cent_mil * 100000 + dec_mil * 10000 + mil * 1000)) / 100;
  int decenas = (points - (cent_mil * 100000 + dec_mil * 10000 + mil * 1000 +
                           centenas * 100)) /
                10;
  int unidades = points - (cent_mil * 100000 + dec_mil * 10000 + mil * 1000 +
                           centenas * 100 + decenas * 10);

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
  _show_number(mil, &rect_pos);

  rect_pos.x = (POINTS_X_POS - 4 * (number_frame_w + PIXEL)) * scale_x;
  _show_number(dec_mil, &rect_pos);

  rect_pos.x = (POINTS_X_POS - 5 * (number_frame_w + PIXEL)) * scale_x;
  _show_number(cent_mil, &rect_pos);
}

void Hud::_show_health(const Player& player) {
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

  if (centenas != 0) {
    rect_pos.x = (HEALTH_X_POS - 2 * (number_frame_w + PIXEL)) * scale_x;
    _show_number(centenas, &rect_pos);
  }
}

void Hud::_show_bullets(const Player& player) {
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

  if (centenas != 0) {
    rect_pos.x = (BULLETS_X_POS - 2 * (number_frame_w + PIXEL)) * scale_x;
    _show_number(centenas, &rect_pos);
  }
}

void Hud::_show_number(int number, SDL_Rect* position) {
  int sprite_x = number % NUMBER_FRAME_X_COUNT;
  SDL_Rect rect_slice = {(sprite_x * (number_frame_w + PIXEL)), 0,
                         number_frame_w, number_frame_h};
  numbers.draw(position, &rect_slice);
}

void Hud::_show_face(const Player& player) {
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

void Hud::_show_key(const Player& player) {
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

void Hud::_show_gun(const Player& player) {
  std::string gun_image_path;
  switch (player.get_gun()) {
    case KNIFE_ID:
      gun_image_path = "../../res/images/hud/IMG_HUD_Knife.png";
      break;
    case PISTOL_ID:
      gun_image_path = "../../res/images/hud/IMG_HUD_Pistol.png";
      break;
    case CHAIN_CANNON_ID:
      gun_image_path = "../../res/images/hud/IMG_HUD_ChainCannon.png";
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

void Hud::_show_player_gun(const Player& player) {
  // TODO MOVE THIS TO WHERE ITS BELONGS
  std::string gun_image_path;
  switch (player.get_gun()) {
    case KNIFE_ID:
      gun_image_path = "../../res/images/guns/knife_shoot.png";
      break;
    case PISTOL_ID:
      gun_image_path = "../../res/images/guns/pistol_shoot.png";
      break;
    case CHAIN_CANNON_ID:
      gun_image_path = "../../res/images/guns/chaincannon_shoot.png";
      break;
    case MACHINE_GUN_ID:
      gun_image_path = "../../res/images/guns/machinegun_shoot.png";
      break;
    case ROCKET_LAUNCHER_ID:
      gun_image_path = "../../res/images/guns/knife_shoot.png";
      break;
    default:
      return;
  }

  Image player_gun(renderer, gun_image_path);
  int frame_width = (player_gun.get_width() - 4 * PIXEL) / 5;
  int frame_height = player_gun.get_height();

  Uint32 sprite_x = 0;

  SDL_Rect rect_gun;
  rect_gun.x = (window.get_width() / 2) - (frame_width * scale_x);
  rect_gun.y = window.get_height() -
               ((background.get_height() + frame_height * 2) * scale_y);
  rect_gun.w = frame_width * 2 * scale_x;
  rect_gun.h = frame_height * 2 * scale_y;

  SDL_Rect rect_slice = {(sprite_x * (frame_width + PIXEL)), 0, frame_width,
                         frame_height};

  player_gun.draw(&rect_gun, &rect_slice);
}
