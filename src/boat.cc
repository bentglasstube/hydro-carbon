#include "boat.h"

#include "graphics.h"
#include "map.h"

namespace {
  const float clean_time = 750.0f;
}

Boat::Boat(Graphics& graphics, unsigned int x, unsigned int y, Direction dir) :
  WaterObject(x, y, 2.0f), cleaning_progress(0.0f)
{
  facing = dir;

  sprites[LEFT]  = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 48, 16, 16, 16));
  sprites[RIGHT] = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 32, 16, 16, 16));
  sprites[UP]    = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 32,  0, 16, 16));
  sprites[DOWN]  = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 48,  0, 16, 16));
}

void Boat::update(boost::shared_ptr<Map> map, unsigned int elapsed) {
  WaterObject::update(map, elapsed);

  if (is_moving()) return;

  if (map->is_oil(x, y)) {
    cleaning_progress += elapsed / clean_time;
    if (cleaning_progress >= 1.0f) {
      cleaning_progress = 0.0f;
      map->clean(x, y);
    }
  } else {
    Direction d = facing;

    if (facing != RIGHT && map->is_oil(x - 1, y)) d = LEFT;
    else if (facing != LEFT && map->is_oil(x + 1, y)) d = RIGHT;
    else if (facing != DOWN && map->is_oil(x, y - 1)) d = UP;
    else if (facing != UP && map->is_oil(x, y + 1)) d = DOWN;
    else {
      int r = rand() % 4;

      if (r == 0) d = static_cast<Direction>((d + 3) % 4);
      if (r == 1) d = static_cast<Direction>((d + 1) % 4);
    }

    switch (d) {
      case UP:
        if (map->sailable(x, y - 1)) start_moving(UP);
        break;

      case DOWN:
        if (map->sailable(x, y + 1)) start_moving(DOWN);
        break;

      case LEFT:
        if (map->sailable(x - 1, y)) start_moving(LEFT);
        break;

      case RIGHT:
        if (map->sailable(x + 1, y)) start_moving(RIGHT);
        break;
    }
  }
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

  sprites[facing]->draw(graphics, dx, dy);
}
