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
    bool moving() { return current_motion != STILL; }

    unsigned int x_pos() { return x; };
    unsigned int y_pos() { return y; };

  private:

    void init_sprites(Graphics& graphics);

    unsigned int x, y, move_progress;
    Motion current_motion, facing;
    bool leaking;

    std::map<Motion, boost::shared_ptr<Sprite>> sprites;
};
