#pragma once

#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Barrel : public WaterObject {
  public:

    Barrel(Graphics& graphics, unsigned int x, unsigned int y);

    void draw(Graphics& graphics);

    const int value() { return 0; }

  private:

    boost::shared_ptr<Sprite> sprite;
};
