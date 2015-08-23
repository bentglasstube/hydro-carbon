#pragma once

#include <boost/shared_ptr.hpp>

#include "particle.h"
#include "sprite.h"

class Smoke : public Particle {
  public:

    Smoke(Graphics& graphics, unsigned int x, unsigned int y, bool dark);
    void draw(Graphics& graphics);

  private:

    boost::shared_ptr<Sprite> sprite;
};
