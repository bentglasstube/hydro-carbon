#pragma once

#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Barrel : public WaterObject {
  public:

    Barrel(Graphics& graphics, int x, int y);

    void draw(Graphics& graphics);

    int value() { return 0; }

  private:

    std::shared_ptr<Sprite> sprite;
};
