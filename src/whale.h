#pragma once

#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Whale : public WaterObject {
  public:
    Whale(Graphics& graphics, unsigned int x, unsigned int y);
    void update(boost::shared_ptr<Map> map, unsigned int elapsed);
    void draw(Graphics& graphics);

  private:
    boost::shared_ptr<Sprite> sprite;
};
