#include "text.h"

Text::Text(Graphics &graphics) : Sprite(graphics, "text", 0, 0, 8, 16) {}

void Text::draw(Graphics& graphics, unsigned int x, unsigned int y, std::string text, Text::Alignment alignment) {
  switch (alignment) {
    case Text::LEFT:
      break;

    case Text::CENTER:
      x -= 4 * text.length();
      break;

    case Text::RIGHT:
      x -= 8 * text.length();
      break;
  }

  for (std::string::iterator i = text.begin(); i != text.end(); ++i) {
    int n = 0;
    if ((*i) >= ' ' && (*i) <= '~') n = (*i) - ' ';

    rect.x = 8 * (n % 16);
    rect.y = 16 * (n / 16);

    Sprite::draw(graphics, x, y);

    x += 8;
  }
}
