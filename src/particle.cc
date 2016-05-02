#include "particle.h"

Particle::Particle(int x, int y, int duration) : x(x), y(y), timer(duration) {}

bool Particle::update(int elapsed) {
  timer -= elapsed;
  return (timer > 0);
}
