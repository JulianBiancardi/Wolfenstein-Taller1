#include "../include/settings.h"

Settings::Settings()
    : screen_width(320),
      screen_height(200),
      fullscreen(false),
      music_volume(50),
      effect_volume(50) {}

Settings::~Settings() {}

void Settings::set_resolution(size_t screen_width, size_t screen_height,
                              bool fullscreen) {
  this->screen_width = screen_width;
  this->screen_height = screen_height;
  this->fullscreen = fullscreen;
}

void Settings::set_music_volume(size_t value) { this->music_volume = value; }

void Settings::set_effect_volume(size_t value) { this->effect_volume = value; }

size_t Settings::get_screen_width() const { return screen_width; }
size_t Settings::get_screen_height() const { return screen_height; }
bool Settings::is_fullscreen() const { return fullscreen; }
size_t Settings::get_music_volume() const { return music_volume; }
size_t Settings::get_effect_volume() const { return effect_volume; }