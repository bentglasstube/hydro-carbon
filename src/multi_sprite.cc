#include "multi_sprite.h"

MultiSprite::MultiSprite(
    Graphics& graphics, const std::string& file,
    int x, int y, int w, int h, int cx
  ) :
  Sprite(graphics, file, x, y, w, h),
  bx(x), by(y), cx(cx) {}

void MultiSprite::draw(Graphics& graphics, int x, int y, int n) {
  rect.x = bx + rect.w * (n % cx);
  rect.y = by + rect.h * (n / cx);

  Sprite::draw(graphics, x, y);
}


