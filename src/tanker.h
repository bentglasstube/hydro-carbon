#pragma once

#include <boost/shared_ptr.hpp>
#include <map>

#include "sprite.h"

class Graphics;

class Tanker {
  public:

    enum Motion { LEFT, RIGHT, UP, DOWN, STILL };

    Tanker(Graphics& graphics, unsigned int x, unsigned int y);

    void update(unsigned int elapsed);
    void draw(Graphics& graphics);

    void start_moving(Motion motion);
    void toggle_leaking() { leaking = !leaking; }

    bool moving() { return current_motion != STILL; }
    bool is_leaking() { return leaking; }

    unsigned int x_pos() { return x; };
    unsigned int y_pos() { return y; };
    unsigned int x_behind() { return facing == LEFT ? x + 1 : facing == RIGHT ? x - 1 : x; }
    unsigned int y_behind() { return facing == UP ? y + 1 : facing == DOWN ? y - 1 : y; }

  private:

    void init_sprites(Graphics& graphics);

    unsigned int x, y, move_progress;
    Motion current_motion, facing;
    bool leaking;

    std::map<Motion, boost::shared_ptr<Sprite>> sprites;
};
