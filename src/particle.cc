#include "particle.h"

Particle::Particle(unsigned int x, unsigned int y, unsigned int duration) : x(x), y(y), timer(duration) {}

bool Particle::update(unsigned int elapsed) {
  timer -= elapsed;
  return (timer > 0);
}
