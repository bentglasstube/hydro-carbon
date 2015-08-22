#pragma once

#include <map>

#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Boat : public WaterObject {
  public:

    Boat(Graphics& graphics, unsigned int x, unsigned int y);

    void update(boost::shared_ptr<Map> map, unsigned int elapsed);
    void draw(Graphics& graphics);

  private:

    std::map<Direction, boost::shared_ptr<Sprite>> sprites;
};
