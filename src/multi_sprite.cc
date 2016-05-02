#include "multi_sprite.h"

MultiSprite::MultiSprite(
    Graphics& graphics, const std::string& file,
    int x, int y, int w, int h, int cx
  ) : file(file), bx(x), by(y), cx(cx)
{
  graphics.load_image(file, true);

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
}

void MultiSprite::draw(Graphics& graphics, int x, int y, int n) {
  rect.x = bx + rect.w * (n % cx);
  rect.y = by + rect.h * (n / cx);

  SDL_Rect dest = { x, y, rect.w, rect.h };

  graphics.blit(file, &rect, &dest);
}


