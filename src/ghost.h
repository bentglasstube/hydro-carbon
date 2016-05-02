#pragma once

#include <boost/shared_ptr.hpp>

#include "particle.h"
#include "sprite.h"

class Ghost : public Particle {
  public:

    Ghost(Graphics& graphics, int x, int y);
    void draw(Graphics& graphics);
    bool update(int elapsed);

  private:
    float dy;
    boost::shared_ptr<Sprite> sprite;
};
