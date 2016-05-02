#pragma once

#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Fish : public WaterObject {
  public:
    Fish(Graphics& graphics, int x, int y);
    void update(boost::shared_ptr<Map> map, int elapsed);
    void draw(Graphics& graphics);

  private:
    boost::shared_ptr<Sprite> sprite;
};
