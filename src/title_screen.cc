#include "title_screen.h"

#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "text.h"

void TitleScreen::init(Graphics& graphics) {
  text.reset(new Text(graphics));
}

bool TitleScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) {
  text->draw(graphics, 320, 232, "Press any key.", Text::CENTER);
}
