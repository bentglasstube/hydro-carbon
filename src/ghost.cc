#include "ghost.h"

#include "animated_sprite.h"
#include "graphics.h"

namespace {
  const float velocity = 24 / 1000.0f;
}

Ghost::Ghost(Graphics& graphics, int x, int y) :
  Particle(x, y, 1000), dy(0.0f)
{
  sprite.reset(new AnimatedSprite(graphics, "boats", 96, 48, 16, 16, 6));
}

void Ghost::draw(Graphics& graphics) {
  sprite->draw(graphics, x, y + dy);
}

bool Ghost::update(int elapsed) {
  dy -= velocity * elapsed;
  return Particle::update(elapsed);
}
