#include "tanker.h"

#include "graphics.h"

Tanker::Tanker(Graphics& graphics, unsigned int x, unsigned int y) :
  WaterObject(x, y, 1.0f), leaking(false)
{
  facing = RIGHT;

  sprites[LEFT]  = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 0, 48, 32, 16));
  sprites[RIGHT] = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 0, 32, 32, 16));
  sprites[UP]    = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 0, 0, 16, 32));
  sprites[DOWN]  = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 16, 0, 16, 32));
}

void Tanker::draw(Graphics& graphics) {
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

void Tanker::start_moving(Direction dir) {
  if (dir == LEFT && facing == RIGHT) return;
  if (dir == RIGHT && facing == LEFT) return;
  if (dir == UP && facing == DOWN) return;
  if (dir == DOWN && facing == UP) return;

  WaterObject::start_moving(dir);
}
