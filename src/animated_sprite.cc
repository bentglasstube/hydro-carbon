#include "animated_sprite.h"

AnimatedSprite::AnimatedSprite(
    Graphics& graphics, const std::string& file,
    unsigned int x, unsigned int y, unsigned int w, unsigned int h,
    unsigned int count
  ) : Sprite(graphics, file, x, y, w, h), bx(x), count(count), start(0) {}

void AnimatedSprite::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  if (start == 0) start = SDL_GetTicks();
  int frame = ((SDL_GetTicks() - start) / AnimatedSprite::frame_duration) % count;

  rect.x = bx + rect.w * frame;
  Sprite::draw(graphics, x, y);
}

