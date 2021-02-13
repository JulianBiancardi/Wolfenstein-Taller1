#ifndef SETTINGS_H
#define SETTINGS_H

#include <stddef.h>

class Settings {
 private:
  size_t screen_width;
  size_t screen_height;
  bool fullscreen;
  size_t music_volume;
  size_t effect_volume;

 public:
  Settings();
  ~Settings();

  /*Change the resolution*/
  void set_resolution(size_t screen_width, size_t screen_height,
                      bool fullscreen);

  /*Change the music volume*/
  void set_music_volume(size_t value);

  /*Change the effect volume*/
  void set_effect_volume(size_t value);

  size_t get_screen_width() const;
  size_t get_screen_height() const;
  bool is_fullscreen() const;
  size_t get_music_volume() const;
  size_t get_effect_volume() const;
};

#endif  // SETTINGS_H