#include "tanker.h"

#include "graphics.h"

Tanker::Tanker(Graphics& graphics, unsigned int x, unsigned int y) :
  x(x), y(y), move_progress(0),
  current_motion(Tanker::STILL), facing(Tanker::RIGHT),
  leaking(false)
{
  init_sprites(graphics);
}

void Tanker::update(unsigned int elapsed) {
  if (moving()) {
    move_progress += elapsed;

    if (move_progress >= 160) {
      switch (current_motion) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        case STILL: break;
      }

      move_progress = 0;
      current_motion = STILL;
    }
  }
}

void Tanker::draw(Graphics& graphics) {
  int dx = x * 16;
  int dy = y * 16;

  switch (current_motion) {
    case LEFT:
      dx -= move_progress / 10;
      break;

    case RIGHT:
      dx += move_progress / 10;
      break;

    case UP:
      dy -= move_progress / 10;
      break;

    case DOWN:
      dy += move_progress / 10;
      break;

    case STILL:
      // do nothing
      break;
  }

  if (facing == RIGHT) dx -= 16;
  if (facing == DOWN) dy -= 16;

  sprites[facing]->draw(graphics, dx, dy);
}

void Tanker::start_moving(Motion motion) {
  if (moving() || motion == Tanker::STILL) return;

  if (facing == LEFT && motion == RIGHT) return;
  if (facing == RIGHT && motion == LEFT) return;
  if (facing == UP && motion == DOWN) return;
  if (facing == DOWN && motion == UP) return;

  current_motion = facing = motion;
}

void Tanker::init_sprites(Graphics& graphics) {
  sprites[Tanker::LEFT] = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 0, 48, 32, 16));
  sprites[Tanker::RIGHT] = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 0, 32, 32, 16));
  sprites[Tanker::UP] = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 0, 0, 16, 32));
  sprites[Tanker::DOWN] = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 16, 0, 16, 32));
}
