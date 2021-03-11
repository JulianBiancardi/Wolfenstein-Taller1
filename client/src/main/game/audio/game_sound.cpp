#include "game_sound.h"

#include <SDL2/SDL_mixer.h>

#include "../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../common/src/main/ids/map_ids.h"
#include "../../../../../common/src/main/paths.h"

#define SOUND_SHOOT 2
#define SOUND_GUARD_DEATH 3
#define SOUND_OPEN_DOOR 4
#define SOUND_CLOSE_DOOR 5
#define SOUND_PICK_GUN 6
#define SOUND_MEDIC_KIT 7
#define SOUND_PICK_CROSS 8
#define SOUND_PICK_CUP_CHEST 9
#define SOUND_SELF_DEATH 10
#define SOUND_KNIFE_MISS 11
#define SOUND_KNIFE_STAB 12
#define SOUND_KNIFE_HIT_1 13
#define SOUND_KNIFE_HIT_2 14
#define SOUND_MACHINE_GUN_SHOOT 15
#define SOUND_CHAIN_CANNON_SHOOT 16
#define SOUND_KNIFE_CHANGE 17
#define SOUND_PISTOL_CHANGE 18
#define SOUND_MACHINE_GUN_CHANGE 19
#define SOUND_CHAIN_CANNON_CHANGE 20

#define OPEN_DOOR 30
#define CLOSE_DOOR 31

GameSound::GameSound(const Point& furthest_point, size_t music_volume,
                     size_t effect_volume)
    : own_point(0, 0),
      music_volume(music_volume),
      effect_volume(effect_volume) {
  double max_distance =
      std::min(Point::distance(Point(0, 0), furthest_point), 50.0);
  this->slope = 1.0 * 255 / (max_distance);

  Mix_Init(MIX_INIT_MP3);

  sound_checker(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048), false);
  Mix_AllocateChannels(16);

  _load_items_sounds();

  sounds.insert(
      {SOUND_SHOOT,
       Mix_LoadWAV(asset_path("res/audio/weapons/deagle-1.wav").c_str())});
  sounds.insert(
      {SOUND_GUARD_DEATH,
       Mix_LoadWAV(asset_path("/res/audio/guard_death.wav").c_str())});
  sounds.insert({SOUND_OPEN_DOOR,
                 Mix_LoadWAV(asset_path("res/audio/open_door.wav").c_str())});
  sounds.insert({SOUND_CLOSE_DOOR,
                 Mix_LoadWAV(asset_path("res/audio/close_door.wav").c_str())});
  sounds.insert({SOUND_SELF_DEATH,
                 Mix_LoadWAV(asset_path("res/audio/death.wav").c_str())});
  sounds.insert(
      {SOUND_KNIFE_MISS,
       Mix_LoadWAV(asset_path("res/audio/knife/knife_hitwall1.wav").c_str())});
  sounds.insert(
      {SOUND_KNIFE_STAB,
       Mix_LoadWAV(asset_path("res/audio/knife/knife_stab.wav").c_str())});
  sounds.insert(
      {SOUND_KNIFE_HIT_1,
       Mix_LoadWAV(asset_path("res/audio/knife/knife_hit1.wav").c_str())});
  sounds.insert(
      {SOUND_KNIFE_HIT_2,
       Mix_LoadWAV(asset_path("res/audio/knife/knife_hit2.wav").c_str())});
  sounds.insert(
      {SOUND_MACHINE_GUN_SHOOT,
       Mix_LoadWAV(asset_path("res/audio/weapons/m4a1-1.wav").c_str())});
  sounds.insert(
      {SOUND_CHAIN_CANNON_SHOOT,
       Mix_LoadWAV(asset_path("res/audio/weapons/m249-1.wav").c_str())});
  sounds.insert(
      {SOUND_KNIFE_CHANGE,
       Mix_LoadWAV(asset_path("res/audio/knife/knife_deploy1.wav").c_str())});
  sounds.insert(
      {SOUND_PISTOL_CHANGE,
       Mix_LoadWAV(asset_path("res/audio/weapons/usp_slideback.wav").c_str())});
  sounds.insert(
      {SOUND_MACHINE_GUN_CHANGE,
       Mix_LoadWAV(asset_path("/res/audio/weapons/m4a1_deploy.wav").c_str())});
  sounds.insert(
      {SOUND_CHAIN_CANNON_CHANGE,
       Mix_LoadWAV(asset_path("res/audio/weapons/m249_chain.wav").c_str())});

  music = Mix_LoadMUS(asset_path("res/audio/background.mp3").c_str());
  if (!music) std::cerr << Mix_GetError();
}

GameSound::~GameSound() {
  for (auto& sound : sounds) {
    Mix_FreeChunk(sound.second);
  }
  Mix_FreeMusic(music);
  Mix_Quit();
}

void GameSound::_load_items_sounds() {
  sounds.insert(
      {CHAIN_CANNON,
       Mix_LoadWAV(asset_path("res/audio/items/chaincannon.wav").c_str())});
  sounds.insert(
      {MACHINE_GUN,
       Mix_LoadWAV(asset_path("res/audio/items/machinegun.wav").c_str())});
  sounds.insert(
      {ROCKET_LAUNCHER,
       Mix_LoadWAV(asset_path("res/audio/items/machinegun.wav").c_str())});
  sounds.insert(
      {BULLETS,
       Mix_LoadWAV(asset_path("res/audio/items/bullets.wav").c_str())});
  sounds.insert(
      {FOOD, Mix_LoadWAV(asset_path("res/audio/items/food.wav").c_str())});
  sounds.insert(
      {MEDKIT, Mix_LoadWAV(asset_path("res/audio/items/medikit.wav").c_str())});
  sounds.insert(
      {CROSS, Mix_LoadWAV(asset_path("res/audio/items/cross.wav").c_str())});
  sounds.insert(
      {CROWN, Mix_LoadWAV(asset_path("res/audio/items/crown.wav").c_str())});
  sounds.insert(
      {CUP, Mix_LoadWAV(asset_path("res/audio/items/cup.wav").c_str())});
  sounds.insert(
      {CHEST, Mix_LoadWAV(asset_path("res/audio/items/chest.wav").c_str())});
  sounds.insert(
      {KEY, Mix_LoadWAV(asset_path("res/audio/items/key.wav").c_str())});
}

void GameSound::play_background() {
  Mix_PlayMusic(music, -1);
  Mix_VolumeMusic(music_volume);
}

void GameSound::play_item_grab(Point point, unsigned char item_id) {
  int channel = Mix_GroupAvailable(-1);

  Mix_Chunk* sound = sounds.at(item_id);

  sound_checker(Mix_SetPosition(channel, 0, map_distance(point)));
  sound_checker(Mix_PlayChannel(channel, sound, 0));
}

void GameSound::play_gun_change(Point point, unsigned char gun_id) {
  int channel = Mix_GroupAvailable(-1);

  Mix_Chunk* sound = nullptr;
  if (gun_id == KNIFE_ID) {
    sound = sounds.at(SOUND_KNIFE_CHANGE);
  } else if (gun_id == PISTOL_ID) {
    sound = sounds.at(SOUND_PISTOL_CHANGE);
  } else if (gun_id == MACHINE_GUN_ID) {
    sound = sounds.at(SOUND_MACHINE_GUN_CHANGE);
  } else if (gun_id == CHAIN_CANNON_ID) {
    sound = sounds.at(SOUND_CHAIN_CANNON_CHANGE);
  } else if (gun_id == ROCKET_LAUNCHER_ID) {
    return;  // TODO Add sound. We couldn't find any good sample online.
  } else {
    return;
  }
  sound_checker(Mix_SetPosition(channel, 0, map_distance(point)));
  sound_checker(Mix_PlayChannel(channel, sound, 0));
}

void GameSound::play_knife(Point point, unsigned char damage,
                           unsigned int objective_id) {
  int channel = Mix_GroupAvailable(-1);

  Mix_Chunk* sound = nullptr;
  if (damage == 0 || objective_id == 0) {
    sound = sounds.at(SOUND_KNIFE_MISS);
  } else if (damage > 8) {
    sound = sounds.at(SOUND_KNIFE_STAB);
  } else {
    if (rand() % 2) {
      sound = sounds.at(SOUND_KNIFE_HIT_1);
    } else {
      sound = sounds.at(SOUND_KNIFE_HIT_2);
    }
  }

  sound_checker(Mix_SetPosition(channel, 0, map_distance(point)));
  sound_checker(Mix_PlayChannel(channel, sound, 0));
}

void GameSound::play_shoot(Point point, unsigned char gun_id) {
  // Mix_PlayChannel(15, sounds.at(SOUND_SHOOT), 0);
  int channel = Mix_GroupAvailable(-1);

  Mix_Chunk* sound = nullptr;
  if (gun_id == PISTOL_ID) {
    Mix_Volume(channel, MIX_MAX_VOLUME / 4);  // MIX_MAX_VOLUME = 128
    sound = sounds.at(SOUND_SHOOT);
  } else if (gun_id == MACHINE_GUN_ID) {
    sound = sounds.at(SOUND_MACHINE_GUN_SHOOT);
  } else if (gun_id == CHAIN_CANNON_ID) {
    sound = sounds.at(SOUND_CHAIN_CANNON_SHOOT);
  } else if (gun_id == ROCKET_LAUNCHER_ID) {
    return;  // TODO Add sound. We couldn't find any online.
  } else {
    return;
  }

  sound_checker(Mix_SetPosition(channel, 0, map_distance(point)));
  sound_checker(Mix_PlayChannel(channel, sound, 0));
}

void GameSound::play_guard_death(Point point) {
  int channel = Mix_GroupAvailable(-1);
  sound_checker(Mix_SetPosition(channel, 0, map_distance(point)));
  sound_checker(Mix_PlayChannel(channel, sounds.at(SOUND_GUARD_DEATH), 0));
}
void GameSound::play_self_death() {
  int channel = Mix_GroupAvailable(-1);
  Mix_PlayChannel(channel, sounds.at(SOUND_SELF_DEATH), 0);
}

void GameSound::play_door(Point point, const int type) {
  int channel = Mix_GroupAvailable(-1);
  sound_checker(Mix_SetPosition(channel, 0, map_distance(point)));
  if (type == OPEN_DOOR) {
    sound_checker(Mix_PlayChannel(channel, sounds.at(SOUND_OPEN_DOOR), 0));
  } else if (type == CLOSE_DOOR) {
    sound_checker(Mix_PlayChannel(channel, sounds.at(SOUND_CLOSE_DOOR), 0));
  }
}

void GameSound::sound_checker(int status) {
  if ((status == 0) || (status == -1)) std::cerr << Mix_GetError() << std::endl;
}
void GameSound::sound_checker(int status, bool error_on_null) {
  if (error_on_null) {
    this->sound_checker(status);
  } else {
    if (status == -1) std::cerr << Mix_GetError() << std::endl;
  }
}

void GameSound::set_point(const Point& point) { this->own_point = point; }

Uint8 GameSound::map_distance(Point point) {
  double distance = Point::distance(this->own_point, point);
  if (distance > 50) return 255;

  double output = round(slope * distance);
  return floor(output + 0.5);
}
