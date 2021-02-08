#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "game_sound.h"

#define SOUND_SHOOT 2
#define SOUND_GUARD_DEATH 3
#define SOUND_OPEN_DOOR 4
#define SOUND_CLOSE_DOOR 5
#define SOUND_PICK_GUN 6
#define SOUND_MEDIC_KIT 7
#define SOUND_PICK_CROSS 8
#define SOUND_PICK_CUP_CHEST 9
#define SOUND_SELF_DEATH 10

#define OPEN_DOOR 30
#define CLOSE_DOOR 31
void GameSound::play_background() {
  Mix_PlayMusic(music, -1);
  Mix_VolumeMusic(30);
}

void GameSound::play_door(Point &point, const int type) {
  int channel = Mix_GroupAvailable(-1);
  sound_checker(Mix_SetPosition(channel, 0, map_distance(point)));
  if (type == OPEN_DOOR){
    sound_checker(Mix_PlayChannel (channel, sounds.at(SOUND_OPEN_DOOR), 0));
  }else if(type == CLOSE_DOOR){
    sound_checker(Mix_PlayChannel (channel, sounds.at(SOUND_CLOSE_DOOR), 0));
  }
}
void GameSound::play_shoot(Point &point) {
  //Mix_PlayChannel(15, sounds.at(SOUND_SHOOT), 0);
  int channel = Mix_GroupAvailable(-1);
  sound_checker(Mix_SetPosition(channel, 0, map_distance(point)));
  sound_checker(Mix_PlayChannel (channel, sounds.at(SOUND_SHOOT), 0));
}

void GameSound::play_guard_death(Point &point) {
  int channel = Mix_GroupAvailable(-1);
  sound_checker(Mix_SetPosition(channel, 0, map_distance(point)));
  sound_checker(Mix_PlayChannel(channel, sounds.at(SOUND_GUARD_DEATH), 0));
}
void GameSound::play_self_death(){
  int channel = Mix_GroupAvailable(-1);
  Mix_PlayChannel(channel, sounds.at(SOUND_SELF_DEATH), 0);
}


GameSound::GameSound(const Point& furthest_point):own_point(0,0){
  double max_distance =
      Point::distance(Point(0,0), furthest_point);
  this->slope = 1.0 * 255 / (max_distance);

  Mix_Init(MIX_INIT_MP3);

  sound_checker(Mix_OpenAudio(
      44100, MIX_DEFAULT_FORMAT, 2, 2048 ), false);
  Mix_AllocateChannels(16);

  sounds.insert({SOUND_SHOOT,
                 Mix_LoadWAV("../src/main/sounds/shoot.wav")});
  sounds.insert({SOUND_GUARD_DEATH,
                 Mix_LoadWAV("../src/main/sounds/guard_death.wav")});
  sounds.insert({SOUND_OPEN_DOOR,
                 Mix_LoadWAV("../src/main/sounds/open_door.wav")});
  sounds.insert({SOUND_CLOSE_DOOR,
                 Mix_LoadWAV("../src/main/sounds/close_door.wav")});
  sounds.insert({SOUND_PICK_GUN,
                 Mix_LoadWAV("../src/main/sounds/gun_item.wav")});
  sounds.insert({SOUND_MEDIC_KIT,
                 Mix_LoadWAV("../src/main/sounds/medic_kit.wav")});
  sounds.insert({SOUND_PICK_CROSS,
                 Mix_LoadWAV("../src/main/sounds/cross_item.wav")});
  sounds.insert({SOUND_PICK_CUP_CHEST,
                 Mix_LoadWAV("../src/main/sounds/cup_item.wav")});
  sounds.insert({SOUND_SELF_DEATH,
                 Mix_LoadWAV("../src/main/sounds/death.wav")});

  music = Mix_LoadMUS("../src/main/sounds/background.mp3");
  if(!music) std::cerr<<Mix_GetError();
}

GameSound::~GameSound() {
  for (auto &sound : sounds) {
    Mix_FreeChunk(sound.second);
  }
  Mix_FreeMusic(music);
  Mix_Quit();
}

void GameSound::sound_checker(const int status) {
  if ((status ==  0) || (status == -1))
    std::cerr << Mix_GetError() << std::endl;
}
void GameSound::sound_checker(const int status, bool error_on_null) {
  if (error_on_null){
    this->sound_checker(status);
  }else{
    if (status == -1)
      std::cerr << Mix_GetError() << std::endl;
  }
}

void GameSound::set_point(const Point& point) {
  this->own_point = point;
  //printf("(%f, %f)", own_point.getX(), own_point.getY());
  //std::cout<<std::endl;
}

Uint8 GameSound::map_distance(Point &point) {
  double output = round(slope * (Point::distance(this->own_point, point)));
  return floor(output + 0.5);
}
