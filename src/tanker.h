#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Tanker : public WaterObject {
  public:

    Tanker(Graphics& graphics, unsigned int x, unsigned int y);

    void draw(Graphics& graphics);
    void start_moving(Direction dir);

    void toggle_leaking() { leaking = !leaking; }
    bool is_leaking() { return leaking; }

    unsigned int x_behind() { return facing == LEFT ? x + 1 : facing == RIGHT ? x - 1 : x; }
    unsigned int y_behind() { return facing == UP ? y + 1 : facing == DOWN ? y - 1 : y; }

  private:

    bool leaking;
    std::map<Direction, boost::shared_ptr<Sprite>> sprites;
};
