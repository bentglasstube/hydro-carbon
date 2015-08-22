#include "game_screen.h"

#include "input.h"

void GameScreen::init(Graphics& graphics) {
  map.reset(new Map(graphics));
  tanker.reset(new Tanker(graphics, 5, 5));
}

bool GameScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  if (input.key_pressed_or_held(SDLK_a)) {
    tanker->start_moving(Tanker::LEFT);
  } else if (input.key_pressed_or_held(SDLK_d)) {
    tanker->start_moving(Tanker::RIGHT);
  } else if (input.key_pressed_or_held(SDLK_w)) {
    tanker->start_moving(Tanker::UP);
  } else if (input.key_pressed_or_held(SDLK_s)) {
    tanker->start_moving(Tanker::DOWN);
  }

  if (input.key_pressed(SDLK_ESCAPE)) return false;

  tanker->update(elapsed);

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  map->draw(graphics);
  tanker->draw(graphics);
}

Screen* GameScreen::next_screen() {
  return NULL;
}

std::string GameScreen::get_music_track() {
  return "";
}
