#include "message.h"

#include "animated_sprite.h"
#include "graphics.h"

Message::Message(Graphics& graphics) {
  text.reset(new Text(graphics));

  box.reset(new Sprite(graphics, "message", 0, 0, 640, 128));
  mouth.reset(new AnimatedSprite(graphics, "message", 0, 128, 32, 16, 5));
}

void Message::update(unsigned int elapsed) {
  if (timer > 0) timer -= elapsed;
}

void Message::draw(Graphics& graphics) {
  if (timer > 0) {
    box->draw(graphics, 0, 352);
    mouth->draw(graphics, 32, 432);
    text->draw(graphics, 96, 368, message);
  }
}

void Message::show(std::string text) {
  timer = 250 * text.length();
  message = text;
}

void Message::dismiss() {
  timer = 0;
}
