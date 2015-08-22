#include "multi_sprite.h"

MultiSprite::MultiSprite(
    Graphics& graphics, const std::string& file,
    unsigned int x, unsigned int y, unsigned int w, unsigned int h,
    unsigned int cx, unsigned int cy
  ) :
  Sprite(graphics, file, x, y, w, h),
  bx(x), by(y), cx(cx), cy(cy) {}

void MultiSprite::draw(Graphics& graphics, unsigned int x, unsigned int y, unsigned int n) {
  rect.x = bx + rect.w * (n % cx);
  rect.y = by + rect.h * (n / cx);

  Sprite::draw(graphics, x, y);
}


