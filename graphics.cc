#include "graphics.h"

Graphics::Graphics(int width, int height) : width(width), height(height) {
  int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

  window = SDL_CreateWindow("Hydro Carbon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * 2, height * 2, flags);
  renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // retro!
  SDL_RenderSetLogicalSize(renderer, width, height);
  SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Graphics::~Graphics() {
  for (TextureMap::iterator i = textures.begin(); i != textures.end(); ++i) {
    SDL_DestroyTexture(i->second);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Graphics::blit(const std::string& file, const SDL_Rect* srect, const SDL_Rect* drect, FlipDirection flip) {
  SDL_RendererFlip f = SDL_FLIP_NONE;
  switch (flip) {
    case HORIZONTAL:
      f = SDL_FLIP_HORIZONTAL;
      break;
    case VERTICAL:
      f = SDL_FLIP_VERTICAL;
      break;
    case BOTH:
      f = (SDL_RendererFlip) (SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL);
      break;
    case NONE:
      f = (SDL_RendererFlip) 0;
      break;
  }
  SDL_Texture* texture = load_image(file);
  SDL_RenderCopyEx(renderer, texture, srect, drect, 0.0f, NULL, f);
}

void Graphics::flip() {
  SDL_RenderPresent(renderer);
}

void Graphics::clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void Graphics::rect(int x, int y, int w, int h, Uint8 red, Uint8 green, Uint8 blue) {
  SDL_Rect r = {x, y, w, h};
  SDL_SetRenderDrawColor(renderer, red, green, blue, 32);
  SDL_RenderFillRect(renderer, &r);
}

SDL_Texture* Graphics::load_image(const std::string& file) {
  const std::string path("content/" + file+ ".bmp");
  if (textures.count(path) == 0) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    const Uint32 black = SDL_MapRGB(surface->format, 0, 0, 0);
    SDL_SetColorKey(surface, SDL_TRUE, black);

    textures[path] = SDL_CreateTextureFromSurface(renderer, surface);
  }

  return textures[path];
}
