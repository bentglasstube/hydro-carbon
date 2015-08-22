#include "water_obj.h"

#include "graphics.h"

WaterObject::WaterObject(unsigned int x, unsigned int y, float speed) :
  x(x), y(y),
  speed(speed), progress(1.0f),
  facing(WaterObject::LEFT) {}

void WaterObject::update(boost::shared_ptr<Map> map, unsigned int elapsed) {
  if (progress < 1.0f) {
    progress += speed * elapsed / 1000.0f / (map->is_oil(x, y) ? 2.0f : 1.0f);

    if (progress >= 1.0f) {
      switch (facing) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
      }

      progress = 1.0f;
    }
  }
}

void WaterObject::start_moving(Direction dir) {
  if (progress < 1.0f) return;

  progress = 0.0f;
  facing = dir;
}
