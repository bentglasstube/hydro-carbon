#pragma once

#include <boost/shared_ptr.hpp>

#include "sprite.h"

class Particle {
  public:

    Particle(
        boost::shared_ptr<Sprite> sprite,
        unsigned int x, unsigned int y,
        unsigned int duration
    );

    bool update(unsigned int elapsed);
    void draw(Graphics& graphics);

  private:

    unsigned int x, y;
    int timer;
    boost::shared_ptr<Sprite> sprite;
    float dx, dy;
};
