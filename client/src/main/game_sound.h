#ifndef WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_GAMESOUND_H_
#define WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_GAMESOUND_H_

#include <SDL2/SDL_mixer.h>

#include <unordered_map>

#include "../../common/src/main/utils/point.h"
class GameSound {
 public:
  GameSound(const Point& furthest_point /*, const Point& own_point*/);
  ~GameSound();
  void play_background();
  void play_shoot(Point& point);
  void play_death(Point& point);
  void play_door(Point& point, const int type);  // 30 -> Open, 31->Close
  void sound_checker(const int status);
  void set_point(const Point& point);

 private:
  Uint8 map_distance(Point& point);
  double slope;
  std::unordered_map<int, Mix_Chunk*> sounds;
  Mix_Music* music;
  Point own_point;

  // const Point& own_point;
};

#endif  // WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_GAMESOUND_H_
