#pragma once

#include <map>

#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Boat : public WaterObject {
  public:

    Boat(Graphics& graphics, unsigned int x, unsigned int y, Direction dir);

    void update(boost::shared_ptr<Map> map, unsigned int elapsed);
    void draw(Graphics& graphics);

    bool is_cleaning() { return cleaning_progress > 0.0f; }

  private:

    Direction next_move(boost::shared_ptr<Map> map);

    std::map<Direction, boost::shared_ptr<Sprite>> sprites;
    float cleaning_progress;
};
