#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

#include "map.h"
#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Police : public WaterObject {
  public:

    Police(Graphics& graphics, int x, int y, Direction dir, boost::shared_ptr<WaterObject> target);

    void update(boost::shared_ptr<Map> map, int elapsed);
    void draw(Graphics& graphics);

  private:

    Direction next_move();

    std::map<Direction, boost::shared_ptr<Sprite>> sprites;
    boost::shared_ptr<WaterObject> target;
};
