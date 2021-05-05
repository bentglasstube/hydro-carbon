#pragma once

#include "sprite.h"

class AnimatedSprite : public Sprite {
  public:

    static const int frame_duration = 128;

    AnimatedSprite(Graphics& graphics, const std::string& file, int x, int y, int w, int h, int count);
    virtual ~AnimatedSprite() {}
    void draw(Graphics& graphics, int x, int y);

  private:

    int bx, count, start;
};
