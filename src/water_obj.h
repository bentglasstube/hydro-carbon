#pragma once

#include <boost/shared_ptr.hpp>

#include "map.h"

class Graphics;

class WaterObject {
  public:

    enum Direction { UP, LEFT, DOWN, RIGHT };

    WaterObject(unsigned int x, unsigned int y, float speed);

    virtual void update(boost::shared_ptr<Map> map, unsigned int elapsed);
    virtual void draw(Graphics& graphics) = 0;
    virtual void start_moving(Direction dir);

    bool is_moving() { return progress < 1.0f; }
    bool is_touching(unsigned int tx, unsigned int ty);

    unsigned int x_pos() { return x; }
    unsigned int y_pos() { return y; }

  protected:

    unsigned int x, y;
    float speed, progress;
    Direction facing;

};
