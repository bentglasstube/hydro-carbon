#include "text.h"

Text::Text(Graphics &graphics) {
  graphics.load_image("text");
}

void Text::draw(Graphics& graphics, int x, int y, const std::string& text, Text::Alignment alignment) {
  SDL_Rect source = { 0, 0, 8, 16 };
  SDL_Rect dest = { x, y, 8, 16 };

  switch (alignment) {
    case Text::LEFT:
      break;

    case Text::CENTER:
      dest.x -= 4 * text.length();
      break;

    case Text::RIGHT:
      dest.x -= 8 * text.length();
      break;
  }

  for (std::string::const_iterator i = text.begin(); i != text.end(); ++i) {
    int n = 0;
    if ((*i) >= ' ' && (*i) <= '~') n = (*i) - ' ';

    source.x = 8 * (n % 16);
    source.y = 16 * (n / 16);

    graphics.blit("text", &source, &dest);

    if ((*i) == '\n' && alignment == LEFT) {
      dest.x = x;
      dest.y += 16;
    } else {
      dest.x += 8;
    }
  }
}
