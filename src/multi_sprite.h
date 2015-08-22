#pragma once

#include "sprite.h"

class MultiSprite : public Sprite {
  public:

    MultiSprite(Graphics& graphics, const std::string& file, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int cx, unsigned int cy);

    void draw(Graphics& graphics, unsigned int x, unsigned int y, unsigned int n);

  private:

    unsigned int bx, by, cx, cy;
};
