#include "boat.h"

#include "graphics.h"
#include "map.h"

namespace {
  const float clean_time = 1000.0f;
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
    switch (next_move(map)) {
      case LEFT:  if (map->sailable(x - 1, y)) start_moving(LEFT);  break;
      case RIGHT: if (map->sailable(x + 1, y)) start_moving(RIGHT); break;
      case UP:    if (map->sailable(x, y - 1)) start_moving(UP);    break;
      case DOWN:  if (map->sailable(x, y + 1)) start_moving(DOWN);  break;
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

static inline bool __check_oil(boost::shared_ptr<Map> map, unsigned int x, unsigned int y, Boat::Direction d) {
  unsigned int dx = x, dy = y;
  switch (d) {
    case Boat::LEFT:  dx--; break;
    case Boat::RIGHT: dx++; break;
    case Boat::UP:    dy--; break;
    case Boat::DOWN:  dy++; break;
  }
  return map->is_oil(dx, dy);
}

Boat::Direction Boat::next_move(boost::shared_ptr<Map> map) {
  Direction left  = static_cast<Direction>((facing + 3) % 4);
  Direction right = static_cast<Direction>((facing + 1) % 4);

  if (__check_oil(map, x, y, facing)) {
    fprintf(stderr, "Oil ahead, continue forward\n");
    return facing;
  }

  bool oil_left = __check_oil(map, x, y, left);
  bool oil_right = __check_oil(map, x, y, right);

  if (oil_left) {
    if (oil_right) {
      fprintf(stderr, "Oil left and right, pick one randomly\n");
      return rand() % 2 == 1 ? left : right;
    } else {
      fprintf(stderr, "Oil left only, go left\n");
      return left;
    }
  } else if (oil_right) {
    fprintf(stderr, "Oil right only, go right\n");
    return right;
  }

  fprintf(stderr, "No oil nearby, go wherever\n");

  switch (rand() % 4) {
    case 0: return left;
    case 1: return right;
    default: return facing;
  }
}

