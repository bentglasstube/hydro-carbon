#include "whale.h"

namespace {
  const int show_interval = 10000;
  const int show_threshold = 1500;
}

Whale::Whale(Graphics& graphics, unsigned int x, unsigned int y) :
  WaterObject(x, y, 0.25f), show_timer(show_threshold)
{
  sprite = boost::shared_ptr<Sprite>(new Sprite(graphics, "boats", 32, 32, 16, 16));
}

void Whale::update(boost::shared_ptr<Map> map, unsigned int elapsed) {
  WaterObject::update(map, elapsed);

  show_timer -= elapsed;
  if (show_timer < 0) show_timer += show_interval;

  if (is_moving()) return;

  Direction d = static_cast<Direction>(rand() % 4);
  switch (d) {
    case UP:
      if (map->is_water(x, y - 1)) start_moving(UP);
      break;

    case DOWN:
      if (map->is_water(x, y + 1)) start_moving(DOWN);
      break;

    case LEFT:
      if (map->is_water(x - 1, y)) start_moving(LEFT);
      break;

    case RIGHT:
      if (map->is_water(x + 1, y)) start_moving(RIGHT);
      break;
  }
}

void Whale::draw(Graphics& graphics) {
  if (show_timer < show_threshold) {
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

    sprite->draw(graphics, dx, dy);
  }
}
