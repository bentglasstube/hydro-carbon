#pragma once

#include "graphics.h"

class MultiSprite {
  public:

    MultiSprite(Graphics& graphics, const std::string& file, int x, int y, int w, int h, int cx);

    void draw(Graphics& graphics, int x, int y, int n);

  private:

    SDL_Rect rect;
    std::string file;
    int bx, by, cx;
};
