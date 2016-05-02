#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Boat : public WaterObject {
  public:

    Boat(Graphics& graphics, int x, int y, Direction dir);

    void update(boost::shared_ptr<Map> map, int elapsed);
    void draw(Graphics& graphics);

    bool is_cleaning() { return cleaning_progress > 0.0f; }

  private:

    Direction next_move(boost::shared_ptr<Map> map);

    std::map<Direction, boost::shared_ptr<Sprite>> sprites;
    float cleaning_progress;
};
