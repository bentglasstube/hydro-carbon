#include "message.h"

#include "animated_sprite.h"
#include "graphics.h"

namespace {
  const unsigned int message_duration = 100;
}

Message::Message(Graphics& graphics) {
  text.reset(new Text(graphics));

  box.reset(new Sprite(graphics, "message", 0, 0, 640, 128));
  mouth.reset(new AnimatedSprite(graphics, "message", 0, 128, 32, 16, 5));
}

void Message::update(unsigned int elapsed) {
  if (timer > 0) {
    timer -= elapsed;
    if (timer <= 0) messages.pop();
  } else if (!messages.empty()) {
    timer = messages.front().length() * message_duration;
  }
}

void Message::draw(Graphics& graphics) {
  if (timer > 0) {
    box->draw(graphics, 0, 16);
    mouth->draw(graphics, 32, 96);
    text->draw(graphics, 96, 32, messages.front());
  }
}

void Message::show(std::string text) {
  messages.push(text);
}

void Message::dismiss() {
  if (!messages.empty()) {
    timer = 0;
    messages.pop();
  }
}
