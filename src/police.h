#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

#include "map.h"
#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Police : public WaterObject {
  public:

    Police(Graphics& graphics, unsigned int x, unsigned int y, Direction dir, boost::shared_ptr<WaterObject> target);

    void update(boost::shared_ptr<Map> map, unsigned int elapsed);
    void draw(Graphics& graphics);

  private:

    Direction next_move();

    std::map<Direction, boost::shared_ptr<Sprite>> sprites;
    boost::shared_ptr<WaterObject> target;
};
