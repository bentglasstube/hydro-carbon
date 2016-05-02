#include "whale.h"

#include "animated_sprite.h"

Whale::Whale(Graphics& graphics, int x, int y) : WaterObject(x, y, 0.25f) {
  // 90 frames makes the whale only appear 10% of the time
  sprite = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "boats", 32, 32, 16, 16, 90));
}

void Whale::update(boost::shared_ptr<Map> map, int elapsed) {
  WaterObject::update(map, elapsed);

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
