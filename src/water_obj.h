#pragma once

#include <memory>

#include "map.h"

class Graphics;

class WaterObject {
  public:

    enum Direction { UP, LEFT, DOWN, RIGHT };

    WaterObject(int x, int y, float speed);

    virtual void update(std::shared_ptr<Map> map, int elapsed);
    virtual void draw(Graphics& graphics) = 0;
    virtual void start_moving(Direction dir);

    bool is_moving() { return progress < 1.0f; }
    bool is_touching(int tx, int ty);

    int x_pos() { return x; }
    int y_pos() { return y; }

  protected:

    void move_if_possible(std::shared_ptr<Map> map, Direction dir);

    int x, y;
    float speed, progress;
    Direction facing;

};
