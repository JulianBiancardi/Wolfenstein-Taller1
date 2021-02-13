#include "hud.h"

#include "../../../../../../common/src/main/ids/gun_ids.h"
#include "../sdl/image.h"
#include "../sdl/text.h"

#define FONT_PATH "../../res/fonts/wolfenstein.ttf"
#define BACKGROUND_PATH "../../res/images/hud/IMG_HUD_Background.png"
#define FACES_PATH "../../res/images/hud/IMG_HUD_BJFaces.png"

#define BACKGROUND_Y_PERCENTAJE 20
#define FACE_Y_PERCENTAJE 20
#define FACE_X_PERCENTAJE 41
#define GUN_Y_PERCENTAJE 18
#define GUN_X_PERCENTAJE 80

#define FACE_FRAME_X_COUNT 3
#define FACE_FRAME_Y_COUNT 7
#define FACE_SCALE 4

Hud::Hud(SDL_Renderer* renderer) : renderer(renderer) {
  size_t font_size = 12;
  font = TTF_OpenFont(FONT_PATH, font_size);
}

Hud::~Hud() {}

void Hud::update(const Window& window, const Player& player) const {
  // TODO MOVE TO CONFIG
  // TODO Move to ResourceManager since this is wasting resources
  _show_background(window);
  _show_stats(window, player);
  _show_face(window, player);
  _show_gun(window, player);
}

void Hud::_show_background(const Window& window) const {
  Image background(renderer, BACKGROUND_PATH);
  SDL_Rect position = {
      0,
      window.get_height() -
          ((window.get_height() * BACKGROUND_Y_PERCENTAJE) / 100),
      window.get_width(),
      ((window.get_height() * BACKGROUND_Y_PERCENTAJE) / 100)};
  background.draw(&position, nullptr);
}

void Hud::_show_stats(const Window& window, const Player& player) const {
  SDL_Color white = {255, 255, 255};
  size_t y_center_pos = window.get_height() - 80;

  Text level(renderer, "1", font, white, 50, y_center_pos);
  Text points(renderer, std::to_string(player.get_points()), font, white, 170,
              y_center_pos);
  Text lives(renderer, std::to_string(player.get_lives()), font, white, 320,
             y_center_pos);
  Text health(renderer, std::to_string(player.get_percentage_health()), font,
              white, 500, y_center_pos);
  Text bullets(renderer, std::to_string(player.get_bullets()), font, white, 640,
               y_center_pos);
}

void Hud::_show_face(const Window& window, const Player& player) const {
  Image face(renderer, FACES_PATH);
  size_t frame_width = face.get_width() / FACE_FRAME_X_COUNT;
  size_t frame_height = face.get_height() / (FACE_FRAME_Y_COUNT + 1);
  size_t health = player.get_percentage_health();

  Uint32 ticks = SDL_GetTicks();
  Uint32 seconds = ticks / 1000;
  Uint32 sprite_x = seconds % FACE_FRAME_X_COUNT;
  Uint32 sprite_y =
      ((100 - health) / (FACE_FRAME_Y_COUNT * 2)) % FACE_FRAME_Y_COUNT;

  SDL_Rect rect_face = {
      ((window.get_width() * FACE_X_PERCENTAJE) / 100),
      window.get_height() - ((window.get_height() * FACE_Y_PERCENTAJE) / 100),
      (int)(frame_width * FACE_SCALE), (int)(frame_height * FACE_SCALE)};
  SDL_Rect rect_slice = {(int)(sprite_x * frame_width),
                         (int)(sprite_y * frame_height), (int)frame_width,
                         (int)frame_height};
  face.draw(&rect_face, &rect_slice);
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
    default:
      gun_image_path = "../../res/images/hud/IMG_HUD_MachineGun.png";
      break;
  }

  Image gun(renderer, gun_image_path);
  SDL_Rect rect_gun = {
      ((window.get_width() * GUN_X_PERCENTAJE) / 100),
      window.get_height() - ((window.get_height() * GUN_Y_PERCENTAJE) / 100),
      window.get_width() - ((window.get_width() * GUN_X_PERCENTAJE) / 100),
      ((window.get_height() * GUN_Y_PERCENTAJE) / 100)};
  gun.draw(&rect_gun, nullptr);
}