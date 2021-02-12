#include "hud.h"

#include "../../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../../common/src/main/utils/rectangle.h"
#include "../sdl/image.h"
#include "../sdl/text.h"

#define FONT_PATH "../src/main/fonts/PixelOperatorMonoHB.ttf"
#define BACKGROUND_PATH "../src/main/game/rendering/hud/ParteInferior.png"

#define BACKGROUND_Y_PERCENTAJE 20
#define GUN_Y_PERCENTAJE 18
#define GUN_X_PERCENTAJE 80

Hud::Hud(SDL_Renderer* renderer) : renderer(renderer) {
  size_t font_size = 12;
  font = TTF_OpenFont(FONT_PATH, font_size);
}

Hud::~Hud() {}

void Hud::update(const Window& window, const Player& player) const {
  // TODO MOVE TO CONFIG
  // TODO Move to ResourceManager since this is wasting resources
  Image background(renderer, BACKGROUND_PATH);
  Rectangle pos(window.get_height() -
                    ((window.get_height() * BACKGROUND_Y_PERCENTAJE) / 100),
                window.get_height(), 0, window.get_width());
  background.draw(pos, nullptr);

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

  std::string gun_image_path;
  switch (player.get_gun()) {
    case KNIFE_ID:
      gun_image_path = "../src/main/game/rendering/hud/IMG_HUD_Knife.png";
      break;
    case PISTOL_ID:
      gun_image_path = "../src/main/game/rendering/hud/IMG_HUD_Pistol.png";
      break;
    case CHAIN_CANNON_ID:
      gun_image_path = "../src/main/game/rendering/hud/IMG_HUD_ChainCanon.png";
      break;
    case MACHINE_GUN_ID:
      gun_image_path = "../src/main/game/rendering/hud/IMG_HUD_MachineGun.png";
      break;
    default:
      gun_image_path = "../src/main/game/rendering/hud/IMG_HUD_MachineGun.png";
      break;
  }

  Image gun(renderer, gun_image_path);
  Rectangle rect_gun(
      window.get_height() - ((window.get_height() * GUN_Y_PERCENTAJE) / 100),
      window.get_height(), ((window.get_width() * GUN_X_PERCENTAJE) / 100),
      window.get_width());
  gun.draw(rect_gun, nullptr);
}