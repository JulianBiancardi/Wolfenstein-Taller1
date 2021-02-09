#ifndef WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_GAMESOUND_H_
#define WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_GAMESOUND_H_

#include <SDL2/SDL_mixer.h>

#include <unordered_map>

#include "../../common/src/main/utils/point.h"
class GameSound {
 public:
  GameSound(const Point& furthest_point);
  ~GameSound();
  void play_background();
  void play_shoot(Point point, unsigned char gun_id);
  void play_knife(Point point, unsigned char damage, unsigned int objective_id);
  void play_guard_death(Point point);
  void play_self_death();
  void play_door(Point point, const int type);  // 30 -> Open, 31->Close
  void set_point(const Point& point);

 private:
  void sound_checker(int status);
  void sound_checker(int status, bool error_on_null);
  Uint8 map_distance(Point point);
  double slope;
  std::unordered_map<int, Mix_Chunk*> sounds;
  Mix_Music* music;
  Point own_point;
};

#endif  // WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_GAMESOUND_H_
