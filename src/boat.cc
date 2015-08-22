#include "boat.h"

#include "graphics.h"

Boat::Boat(Graphics& graphics, unsigned int x, unsigned int y) :
  WaterObject(x, y, 2.0f)
{
  facing = static_cast<Direction>(rand() % 4);

  sprites[LEFT]  = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 48, 16, 16, 16));
  sprites[RIGHT] = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 32, 16, 16, 16));
  sprites[UP]    = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 32,  0, 16, 16));
  sprites[DOWN]  = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 48,  0, 16, 16));
}

void Boat::draw(Graphics& graphics) {
  int dx = x * 16;
  int dy = y * 16;

  if (is_moving()) {
    switch (facing) {
      case LEFT: dx -= progress * 16; break;
      case RIGHT: dx += progress * 16; break;
      case UP: dy -= progress * 16; break;
      case DOWN: dy += progress * 16; break;
    }
  }

  if (facing == RIGHT) dx -= 16;
  if (facing == DOWN) dy -= 16;

  sprites[facing]->draw(graphics, dx, dy);
}
