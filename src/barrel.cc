#include "barrel.h"

#include "animated_sprite.h"

Barrel::Barrel(Graphics& graphics, unsigned int x, unsigned int y) : WaterObject(x, y, 0.0f) {
  sprite = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "boats", 64, 0, 16, 16, 8));
}

void Barrel::draw(Graphics& graphics) {
  sprite->draw(graphics, x * 16, y * 16);
}
