#include "smoke.h"

#include "animated_sprite.h"
#include "graphics.h"

namespace {
  const int frame_count = 3;
}

Smoke::Smoke(Graphics& graphics, int x, int y, bool dark = false) :
  Particle(x, y, frame_count * AnimatedSprite::frame_duration)
{
  sprite.reset(new AnimatedSprite(graphics, "boats", 64 + (dark ? 48 : 0), 16, 16, 16, frame_count));
}

void Smoke::draw(Graphics& graphics) {
  sprite->draw(graphics, x, y);
}
