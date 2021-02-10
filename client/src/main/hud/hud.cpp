#include "hud.h"

#include "../../../../common/src/main/ids/gun_ids.h"
#include "../sdl/image.h"
#include "../sdl/text.h"

#define UNIT 3
#define SCREEN_WIDTH (320 * UNIT)
#define SCREEN_HEIGHT (200 * UNIT)
#define BACKGROUND_PATH "../src/main/hud/IMG_HUD_Background.png"

Hud::Hud(SDL_Renderer* renderer) : renderer(renderer) {}

Hud::~Hud() {}

void Hud::update(const Player& player) const {
  // TODO MOVE TO CONFIG
  Image background(renderer, BACKGROUND_PATH);
  SDL_Rect rect = {0, SCREEN_HEIGHT - (background.get_height() * 3),
                   SCREEN_WIDTH, background.get_height() * 3};
  background.draw(&rect, nullptr);

  SDL_Color white = {255, 255, 255};
  size_t font_size = 12;
  size_t y_center_pos = SCREEN_HEIGHT - 80;

  Text level(renderer, "1", 14, white, 50, y_center_pos);
  Text points(renderer, std::to_string(player.get_points()), font_size, white,
              170, y_center_pos);
  Text lives(renderer, std::to_string(player.get_lives()), font_size, white,
             320, y_center_pos);
  Text health(renderer, std::to_string(player.get_health()), font_size, white,
              500, y_center_pos);
  Text bullets(renderer, std::to_string(player.get_bullets()), font_size, white,
               640, y_center_pos);

  std::string gun_image_path;
  switch (player.get_gun()) {
    case KNIFE_ID:
      gun_image_path = "../src/main/hud/IMG_HUD_Knife.png";
      break;
    case PISTOL_ID:
      gun_image_path = "../src/main/hud/IMG_HUD_Pistol.png";
      break;
    case CHAIN_CANNON_ID:
      gun_image_path = "../src/main/hud/IMG_HUD_ChainCanon.png";
      break;
    case MACHINE_GUN_ID:
      gun_image_path = "../src/main/hud/IMG_HUD_MachineGun.png";
      break;
    default:
      break;
  }

  Image gun(renderer, gun_image_path);
  SDL_Rect rect_gun = {760, SCREEN_HEIGHT - 100, gun.get_width() * 3,
                       gun.get_height() * 3};
  gun.draw(&rect_gun, nullptr);
}