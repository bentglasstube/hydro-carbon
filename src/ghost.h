#pragma once

#include <boost/shared_ptr.hpp>

#include "particle.h"
#include "sprite.h"

class Ghost : public Particle {
  public:

    Ghost(Graphics& graphics, unsigned int x, unsigned int y);
    void draw(Graphics& graphics);
    bool update(unsigned int elapsed);

  private:
    float dy;
    boost::shared_ptr<Sprite> sprite;
};
