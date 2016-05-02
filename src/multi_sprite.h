#pragma once

#include "sprite.h"

class MultiSprite : public Sprite {
  public:

    MultiSprite(Graphics& graphics, const std::string& file, int x, int y, int w, int h, int cx);

    void draw(Graphics& graphics, int x, int y, int n);

  private:

    int bx, by, cx;
};
