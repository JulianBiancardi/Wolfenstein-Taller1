#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Label {
 private:
  SDL_Texture* texture = nullptr;

 public:
  Label(SDL_Renderer* renderer, const std::string& text, TTF_Font* font,
        SDL_Color color = SDL_Color({0xFF, 0xFF, 0xFF, 0xFF}));

  Label(Label&& other) = delete;             // No move constructor
  Label& operator=(Label&& other) = delete;  // No move constructor

  ~Label();
};

#endif /*LABEL_H*/
