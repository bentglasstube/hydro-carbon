#include "title_screen.h"

#include "audio.h"
#include "game_screen.h"
#include "graphics.h"
#include "input.h"

void TitleScreen::init(Graphics& graphics) {
  backdrop.reset(new Backdrop(graphics, "title"));
  text.reset(new Text(graphics));
}

bool TitleScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);
  text->draw(graphics, 320, 416, "Press any key.", Text::CENTER);
}

Screen* TitleScreen::next_screen() {
  return new GameScreen();
}
