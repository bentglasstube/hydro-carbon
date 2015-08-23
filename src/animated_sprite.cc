#include "animated_sprite.h"

AnimatedSprite::AnimatedSprite(
    Graphics& graphics, const std::string& file,
    unsigned int x, unsigned int y, unsigned int w, unsigned int h,
    unsigned int count
  ) : Sprite(graphics, file, x, y, w, h), bx(x), count(count) {}

void AnimatedSprite::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  int frame = (SDL_GetTicks() / AnimatedSprite::frame_duration) % count;
  rect.x = bx + rect.w * frame;
  Sprite::draw(graphics, x, y);
}

