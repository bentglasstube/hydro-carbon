#pragma once

#include <memory>

#include "particle.h"
#include "sprite.h"

class Ghost : public Particle {
  public:

    Ghost(Graphics& graphics, int x, int y);
    void draw(Graphics& graphics);
    bool update(int elapsed);

  private:
    float dy;
    std::shared_ptr<Sprite> sprite;
};
