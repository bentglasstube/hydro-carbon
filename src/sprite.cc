#include "sprite.h"

#include "graphics.h"

Sprite::Sprite(Graphics& graphics, const std::string& file, int x, int y, int w, int h) {
  this->file = file;

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  // Force transparency enabled
  graphics.load_image(file, true);
}

void Sprite::draw(Graphics& graphics, int x, int y) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;
  dest.w = rect.w;
  dest.h = rect.h;

  graphics.blit(file, &rect, &dest);
}
