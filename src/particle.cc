#include "particle.h"

Particle::Particle(boost::shared_ptr<Sprite> sprite, unsigned int x, unsigned int y, unsigned int duration) :
  x(x), y(y), timer(duration), sprite(sprite)
{
  dx = 0;
  dy = 0;
}

bool Particle::update(unsigned int elapsed) {
  timer -= elapsed;

  /* x += dx * elapsed / 16; */
  /* y += dy * elapsed / 16; */

  return (timer > 0);
}

void Particle::draw(Graphics& graphics) {
  if (timer > 0) sprite->draw(graphics, x, y);
}
