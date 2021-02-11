#include "hud.h"

#include "../../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../../common/src/main/utils/rectangle.h"
#include "../sdl/image.h"
#include "../sdl/text.h"

#define FONT_PATH "../src/main/fonts/PixelOperatorMonoHB.ttf"

#define UNIT 3
#define SCREEN_WIDTH (320 * UNIT)
#define SCREEN_HEIGHT (200 * UNIT)
#define BACKGROUND_PATH "../src/main/game/rendering/hud/ParteInferior.png"

Hud::Hud(SDL_Renderer* renderer) : renderer(renderer) {
  size_t font_size = 12;
  font = TTF_OpenFont(FONT_PATH, font_size);
}

Hud::~Hud() {}

void Hud::update(const Player& player) const {
  // TODO MOVE TO CONFIG
  // TODO Move to ResourceManager since this is wasting resources
  Image background(renderer, BACKGROUND_PATH);
  Rectangle pos(SCREEN_HEIGHT - (background.get_height() * UNIT), SCREEN_HEIGHT,
                0, SCREEN_WIDTH);
  background.draw(pos, nullptr);

  SDL_Color white = {255, 255, 255};
  size_t y_center_pos = SCREEN_HEIGHT - 80;

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
      SCREEN_HEIGHT - (background.get_height() * UNIT) + (2 * UNIT),
      SCREEN_HEIGHT - (2 * UNIT), 770, SCREEN_WIDTH - (2 * UNIT));
  gun.draw(rect_gun, nullptr);
}