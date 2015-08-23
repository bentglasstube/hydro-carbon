#include "police.h"

#include "animated_sprite.h"
#include "graphics.h"

Police::Police(Graphics& graphics, unsigned int x, unsigned int y, Direction dir, boost::shared_ptr<WaterObject> target) :
  WaterObject(x, y, 3.0f), target(target)
{
  facing = dir;

  sprites[LEFT]  = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "boats", 64, 64, 16, 16, 4));
  sprites[RIGHT] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "boats", 64, 80, 16, 16, 4));
  sprites[UP]    = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "boats",  0, 64, 16, 16, 4));
  sprites[DOWN]  = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "boats",  0, 80, 16, 16, 4));
}

void Police::update(boost::shared_ptr<Map> map, unsigned int elapsed) {
  WaterObject::update(map, elapsed);
  if (!is_moving()) move_if_possible(map, next_move());
}

void Police::draw(Graphics& graphics) {
  int dx = x * 16;
  int dy = y * 16;

  if (is_moving()) {
    switch (facing) {
      case LEFT:  dx -= progress * 16; break;
      case RIGHT: dx += progress * 16; break;
      case UP:    dy -= progress * 16; break;
      case DOWN:  dy += progress * 16; break;
    }
  }

  sprites[facing]->draw(graphics, dx, dy);
}

Police::Direction Police::next_move() {
  switch (facing) {
    case LEFT:
      if (target->x_pos() < x) return LEFT;
      return target->y_pos() < y ? UP : DOWN;

    case RIGHT:
      if (target->x_pos() > x) return RIGHT;
      return target->y_pos() < y ? UP : DOWN;

    case UP:
      if (target->y_pos() < y) return UP;
      return target->x_pos() < x ? LEFT : RIGHT;

    case DOWN:
      if (target->y_pos() > y) return DOWN;
      return target->x_pos() < x ? LEFT : RIGHT;
  }
}
