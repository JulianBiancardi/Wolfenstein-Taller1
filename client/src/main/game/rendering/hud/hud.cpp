#include "hud.h"

#include <iostream>  //TODO DELET

#include "../../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../../common/src/main/utils/rectangle.h"
#include "../sdl/text.h"

#define FONT_PATH "../../res/fonts/wolfenstein.ttf"
#define BACKGROUND_PATH "../../res/images/hud/IMG_HUD_Background.png"
#define BJ_FACES_PATH "../../res/images/hud/IMG_HUD_BJFaces.png"

#define PIXEL 1

#define BACKGROUND_Y_PERCENTAJE 20
#define FACE_Y_PERCENTAJE 19
#define FACE_X_PERCENTAJE 42
#define GUN_Y_PERCENTAJE 18
#define GUN_X_PERCENTAJE 80

#define LEVEL_X_POS 4
#define POINTS_X_POS 18
#define LIVES_X_POS 32
#define HEALTH_X_POS 52
#define BULLETS_X_POS 68
#define STATS_Y_POS 12

#define FACE_FRAME_X_COUNT 3
#define FACE_FRAME_Y_COUNT 7
#define FACE_SCALE 4

Hud::Hud(SDL_Renderer* renderer)
    : renderer(renderer),
      background(renderer, BACKGROUND_PATH),
      bj_faces(renderer, BJ_FACES_PATH) {
  size_t font_size = 12;
  font = TTF_OpenFont(FONT_PATH, font_size);
}

Hud::~Hud() {}

void Hud::update(const Window& window, const Player& player) {
  // TODO MOVE TO CONFIG
  // TODO Move to ResourceManager since this is wasting resources
  _show_background(window);
  _show_stats(window, player);
  _show_face(window, player);
  _show_gun(window, player);
}

void Hud::_show_background(const Window& window) {
  Rectangle pos(window.get_height() -
                    ((window.get_height() * BACKGROUND_Y_PERCENTAJE) / 100),
                window.get_height(), 0, window.get_width());
  background.draw(pos, nullptr);
}

void Hud::_show_stats(const Window& window, const Player& player) const {
  SDL_Color white = {255, 255, 255};
  size_t y_center_pos =
      window.get_height() - ((window.get_height() * STATS_Y_POS) / 100);

  size_t level_pos = ((window.get_width() * LEVEL_X_POS) / 100);
  size_t points_pos = ((window.get_width() * POINTS_X_POS) / 100);
  size_t lives_pos = ((window.get_width() * LIVES_X_POS) / 100);
  size_t health_pos = ((window.get_width() * HEALTH_X_POS) / 100);
  size_t bullets_pos = ((window.get_width() * BULLETS_X_POS) / 100);

  Text level(renderer, "1", font, white, level_pos, y_center_pos);
  Text points(renderer, std::to_string(player.get_points()), font, white,
              points_pos, y_center_pos);
  Text lives(renderer, std::to_string(player.get_lives()), font, white,
             lives_pos, y_center_pos);
  Text health(renderer, std::to_string(player.get_percentage_health()), font,
              white, health_pos, y_center_pos);
  Text bullets(renderer, std::to_string(player.get_bullets()), font, white,
               bullets_pos, y_center_pos);
}

void Hud::_show_face(const Window& window, const Player& player) {
  size_t frame_width = (bj_faces.get_width() - 2 * PIXEL) / FACE_FRAME_X_COUNT;
  size_t frame_height =
      (bj_faces.get_height() - 7 * PIXEL) / (FACE_FRAME_Y_COUNT + 1);
  size_t health = player.get_percentage_health();

  Uint32 ticks = SDL_GetTicks();
  Uint32 seconds = ticks / 1000;
  Uint32 sprite_x = seconds % FACE_FRAME_X_COUNT;
  Uint32 sprite_y =
      ((100 - health) / (FACE_FRAME_Y_COUNT * 2)) % FACE_FRAME_Y_COUNT;

  SDL_Rect rect_face = {
      ((window.get_width() * FACE_X_PERCENTAJE) / 100),
      window.get_height() - ((window.get_height() * FACE_Y_PERCENTAJE) / 100),
      frame_width * FACE_SCALE, (frame_height * FACE_SCALE) - 2 * PIXEL};
  SDL_Rect rect_slice = {sprite_x * (frame_width + PIXEL),
                         sprite_y * (frame_height + PIXEL), frame_width,
                         frame_height};
  bj_faces.draw(&rect_face, &rect_slice);
}

void Hud::_show_gun(const Window& window, const Player& player) const {
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
      gun_image_path = "../../res/images/hud/IMG_HUD_MachineGun.png";
      break;
  }

  Image gun(renderer, gun_image_path);
  Rectangle rect_gun(
      window.get_height() - ((window.get_height() * GUN_Y_PERCENTAJE) / 100),
      window.get_height(), ((window.get_width() * GUN_X_PERCENTAJE) / 100),
      window.get_width());
  gun.draw(rect_gun, nullptr);
}