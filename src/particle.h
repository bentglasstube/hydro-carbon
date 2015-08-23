#pragma once

#include <boost/shared_ptr.hpp>

class Graphics;

class Particle {
  public:

    Particle(unsigned int x, unsigned int y, unsigned int duration);
    virtual bool update(unsigned int elapsed);
    virtual void draw(Graphics& graphics) = 0;

  protected:
    unsigned int x, y;

  private:
    int timer;
};
