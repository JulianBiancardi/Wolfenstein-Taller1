#include "game_sound.h"

#include <SDL2/SDL_mixer.h>

#include "../../../../../common/src/main/ids/gun_ids.h"

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
#define AUDIO_PATH "../../res/audio/"
void GameSound::play_background() {
  Mix_PlayMusic(music, -1);
  Mix_VolumeMusic(30);
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
    return;  // TODO Add sound
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
    return;  // TODO Add sound
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

GameSound::GameSound(const Point& furthest_point) : own_point(0, 0) {
  double max_distance =
      std::min(Point::distance(Point(0, 0), furthest_point), 50.0);
  this->slope = 1.0 * 255 / (max_distance);

  Mix_Init(MIX_INIT_MP3);

  sound_checker(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048), false);
  Mix_AllocateChannels(16);

  sounds.insert(
      {SOUND_SHOOT, Mix_LoadWAV("../../res/audio/weapons/deagle-1.wav")});
  sounds.insert(
      {SOUND_GUARD_DEATH, Mix_LoadWAV("../../res/audio/guard_death.wav")});
  sounds.insert(
      {SOUND_OPEN_DOOR, Mix_LoadWAV("../../res/audio/open_door.wav")});
  sounds.insert(
      {SOUND_CLOSE_DOOR, Mix_LoadWAV("../../res/audio/close_door.wav")});
  sounds.insert({SOUND_PICK_GUN, Mix_LoadWAV("../../res/audio/gun_item.wav")});
  sounds.insert(
      {SOUND_MEDIC_KIT, Mix_LoadWAV("../../res/audio/medic_kit.wav")});
  sounds.insert(
      {SOUND_PICK_CROSS, Mix_LoadWAV("../../res/audio/cross_item.wav")});
  sounds.insert(
      {SOUND_PICK_CUP_CHEST, Mix_LoadWAV("../../res/audio/cup_item.wav")});
  sounds.insert({SOUND_SELF_DEATH, Mix_LoadWAV("../../res/audio/death.wav")});
  sounds.insert({SOUND_KNIFE_MISS,
                 Mix_LoadWAV("../../res/audio/knife/knife_hitwall1.wav")});
  sounds.insert(
      {SOUND_KNIFE_STAB, Mix_LoadWAV("../../res/audio/knife/knife_stab.wav")});
  sounds.insert(
      {SOUND_KNIFE_HIT_1, Mix_LoadWAV("../../res/audio/knife/knife_hit1.wav")});
  sounds.insert(
      {SOUND_KNIFE_HIT_2, Mix_LoadWAV("../../res/audio/knife/knife_hit2.wav")});
  sounds.insert({SOUND_MACHINE_GUN_SHOOT,
                 Mix_LoadWAV("../../res/audio/weapons/m4a1-1.wav")});
  sounds.insert({SOUND_CHAIN_CANNON_SHOOT,
                 Mix_LoadWAV("../../res/audio/weapons/m249-1.wav")});
  sounds.insert({SOUND_KNIFE_CHANGE,
                 Mix_LoadWAV("../../res/audio/knife/knife_deploy1.wav")});
  sounds.insert({SOUND_PISTOL_CHANGE,
                 Mix_LoadWAV("../../res/audio/weapons/usp_slideback.wav")});
  sounds.insert({SOUND_MACHINE_GUN_CHANGE,
                 Mix_LoadWAV("../../res/audio/weapons/m4a1_deploy.wav")});
  sounds.insert({SOUND_CHAIN_CANNON_CHANGE,
                 Mix_LoadWAV("../../res/audio/weapons/m249_chain.wav")});

  music = Mix_LoadMUS("../../res/audio/background.mp3");
  if (!music) std::cerr << Mix_GetError();
}

GameSound::~GameSound() {
  for (auto& sound : sounds) {
    Mix_FreeChunk(sound.second);
  }
  Mix_FreeMusic(music);
  Mix_Quit();
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

void GameSound::set_point(const Point& point) {
  this->own_point = point;
  // printf("(%f, %f)", own_point.getX(), own_point.getY());
  // std::cout<<std::endl;
}

Uint8 GameSound::map_distance(Point point) {
  double distance = Point::distance(this->own_point, point);
  //  printf("||||||||||||||||||||||Yo(%f, %f)-El(%f, %f)
  //  Dist(%f)||||||||||||||||||||||", own_point.getX(),
  //  own_point.getY(), point.getX(), point.getY(), distance);
  if (distance > 50) return 255;
  double output = round(slope * distance);
  return floor(output + 0.5);
}
