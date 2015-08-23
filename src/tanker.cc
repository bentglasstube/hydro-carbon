#include "tanker.h"

#include "audio.h"
#include "graphics.h"

#include "animated_sprite.h"

namespace {
  const int leak_duration = 5000;
  const int boost_duration = 5000;
}

Tanker::Tanker(Graphics& graphics, unsigned int x, unsigned int y) :
  WaterObject(x, y, 1.0f),
  barrels(5), lawyers(0), celebs(0),
  leak_timer(0), boost_timer(0)
{
  facing = RIGHT;

  sprites[LEFT]  = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 0, 48, 32, 16));
  sprites[RIGHT] = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 0, 32, 32, 16));
  sprites[UP]    = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 0, 0, 16, 32));
  sprites[DOWN]  = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 16, 0, 16, 32));
}

void Tanker::update(boost::shared_ptr<Map> map, unsigned int elapsed) {
  WaterObject::update(map, elapsed);

  if (leak_timer > 0) {
    leak_timer -= elapsed;
    if (leak_timer <= 0) {
      leak_timer = 0;
    }
  }

  if (boost_timer > 0) {
    boost_timer -= elapsed;
    if (boost_timer <= 0) {
      speed /= 3.0f;
      boost_timer = 0;
    }
  }
}

void Tanker::draw(Graphics& graphics) {
  sprites[facing]->draw(graphics, x_draw(), y_draw());
}

void Tanker::start_moving(Direction dir) {
  if (dir == LEFT && facing == RIGHT) return;
  if (dir == RIGHT && facing == LEFT) return;
  if (dir == UP && facing == DOWN) return;
  if (dir == DOWN && facing == UP) return;

  WaterObject::start_moving(dir);
}

void Tanker::start_leaking(Audio& audio) {
  if (is_leaking() || is_boosting() || barrels == 0) {
    audio.play_sample("nope");
  } else {
    barrels--;
    leak_timer = leak_duration;

    audio.play_sample("drop");
  }
}

void Tanker::boost(Audio& audio) {
  if (is_leaking() || is_boosting() || barrels == 0) {
    audio.play_sample("nope");
  } else {
    barrels--;
    boost_timer = boost_duration;
    speed *= 3;

    audio.play_sample("boost");
  }
}

unsigned int Tanker::x_smoke() {
  switch (facing) {
    case LEFT:  return x_draw() + 24;
    case RIGHT: return x_draw() - 8;
    default:    return x_draw() + rand() % 5 - 2;
  }
}

unsigned int Tanker::y_smoke() {
  switch (facing) {
    case UP:   return y_draw() + 24;
    case DOWN: return y_draw() - 8;
    default:   return y_draw() + rand() % 5 - 2;
  }
}

unsigned int Tanker::x_draw() {
  switch (facing) {
    case LEFT:  return 16 * (x - (is_moving() ? progress : 0)) - 8;
    case RIGHT: return 16 * (x + (is_moving() ? progress : 0)) - 8;
    default:    return 16 * x;
  }
}

unsigned int Tanker::y_draw() {
  switch (facing) {
    case UP:   return 16 * (y - (is_moving() ? progress : 0)) - 8;
    case DOWN: return 16 * (y + (is_moving() ? progress : 0)) - 8;
    default:   return 16 * y;
  }
}
