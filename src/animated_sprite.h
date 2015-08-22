#pragma once

#include "sprite.h"

class AnimatedSprite : public Sprite {
  public:

    AnimatedSprite(Graphics& graphics, const std::string& file, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int count);
    void draw(Graphics& graphics, unsigned int x, unsigned int y);

  private:

    unsigned int bx, count;
};
