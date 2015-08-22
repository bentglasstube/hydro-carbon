#pragma once

class Graphics;

class WaterObject {
  public:

    enum Direction { LEFT, RIGHT, UP, DOWN };

    WaterObject(unsigned int x, unsigned int y, float speed);

    void update(unsigned int elapsed);
    virtual void draw(Graphics& graphics) = 0;
    virtual void start_moving(Direction dir);

    bool is_moving() { return progress < 1.0f; }

    unsigned int x_pos() { return x; }
    unsigned int y_pos() { return y; }

  protected:

    unsigned int x, y;
    float speed, progress;
    Direction facing;

};
