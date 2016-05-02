#include "text.h"

Text::Text(Graphics &graphics) : Sprite(graphics, "text", 0, 0, 8, 16) {}

void Text::draw(Graphics& graphics, int x, int y, std::string text, Text::Alignment alignment) {
  int dx = 0, dy = 0;

  switch (alignment) {
    case Text::LEFT:
      break;

    case Text::CENTER:
      dx = -4 * text.length();
      break;

    case Text::RIGHT:
      dx = -8 * text.length();
      break;
  }

  for (std::string::iterator i = text.begin(); i != text.end(); ++i) {
    int n = 0;
    if ((*i) >= ' ' && (*i) <= '~') n = (*i) - ' ';

    if ((*i) == '\n') {
      dx = 0;
      dy += 16;
    } else {
      rect.x = 8 * (n % 16);
      rect.y = 16 * (n / 16);
      Sprite::draw(graphics, x + dx, y + dy);
      dx += 8;
    }
  }
}
