#pragma once

#include <map>

#include <memory>

#include "map.h"
#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Police : public WaterObject {
  public:

    Police(Graphics& graphics, int x, int y, Direction dir, std::shared_ptr<WaterObject> target);

    void update(std::shared_ptr<Map> map, int elapsed);
    void draw(Graphics& graphics);

  private:

    Direction next_move();

    std::map<Direction, std::shared_ptr<Sprite>> sprites;
    std::shared_ptr<WaterObject> target;
};
