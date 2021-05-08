#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>

class Graphics {
  public:

    Graphics(int width, int height);
    ~Graphics();

    enum FlipDirection { NONE, HORIZONTAL, VERTICAL, BOTH };

    void blit(const std::string& file, const SDL_Rect* srect, const SDL_Rect* drect, FlipDirection flip = NONE);
    void flip();
    void clear();

    void rect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);

    int get_width() { return width; }
    int get_height() { return height; }

    SDL_Texture* load_image(const std::string& file);

  private:

    int width, height;
    typedef std::map<std::string, SDL_Texture*> TextureMap;
    TextureMap textures;
    SDL_Window* window;
    SDL_Renderer* renderer;
};
