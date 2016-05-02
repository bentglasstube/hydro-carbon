#include "fish.h"

#include "animated_sprite.h"

Fish::Fish(Graphics& graphics, unsigned int x, unsigned int y) :
  WaterObject(x, y, 0.1f)
{
  sprite = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "boats", 32, 48, 16, 16, 4));
}

void Fish::update(boost::shared_ptr<Map> map, unsigned int elapsed) {
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

void Fish::draw(Graphics& graphics) {
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
