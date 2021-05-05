#pragma once

#include <memory>

#include "particle.h"
#include "sprite.h"

class Smoke : public Particle {
  public:

    Smoke(Graphics& graphics, int x, int y, bool dark);
    void draw(Graphics& graphics);

  private:

    std::shared_ptr<Sprite> sprite;
};
