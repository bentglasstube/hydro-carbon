#pragma once

#include <memory>

class Graphics;

class Particle {
  public:

    Particle(int x, int y, int duration);
    virtual ~Particle() {}
    virtual bool update(int elapsed);
    virtual void draw(Graphics& graphics) = 0;

  protected:
    int x, y;

  private:
    int timer;
};
