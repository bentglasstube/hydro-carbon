#include "game_over_screen.h"

#include <boost/format.hpp>

#include "input.h"
#include "game_screen.h"
#include "graphics.h"
#include "title_screen.h"

namespace {
  const int interval = 500;
}

void GameOverScreen::init(Graphics& graphics) {
  backdrop.reset(new Backdrop(graphics, "backdrop"));
  text.reset(new Text(graphics));
  title.reset(new Sprite(graphics, "gameover", 0, 0, 640, 96));

  icon_whale.reset(new Sprite(graphics, "ui", 0, 48, 32, 16));
  icon_fish.reset(new Sprite(graphics, "ui", 32, 48, 16, 16));

  fish_drawn = whales_drawn = 0;
  text_drawn = false;

  timer = interval * 3;
}

bool GameOverScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  timer -= elapsed;

  if (timer < 0) {
    timer += interval;

    if (whales > 0) {
      whales_drawn++;
      if (--whales == 0) timer += 2 * interval;
    } else if (fish > 0) {
      fish_drawn++;
      if (--fish == 0) timer += 2 * interval;
    } else {
      text_drawn = true;
    }
  }

  if (text_drawn) {
    if (input.key_pressed(SDLK_q)) {
      choice = REPLAY;
      return false;
    } else if (input.key_pressed(SDLK_e)) {
      choice = MENU;
      return false;
    } else if (input.key_pressed(SDLK_ESCAPE)) {
      choice = QUIT;
      return false;
    }
  } else {
    if (input.any_pressed()) {
      text_drawn = true;
      whales_drawn += whales;
      fish_drawn += fish;
      whales = fish = 0;
    }
  }

  return true;
}

void GameOverScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);
  title->draw(graphics, 0, 48);

  unsigned int y = 160;

  if (fish_drawn > 0 || whales_drawn > 0) {
    text->draw(graphics, 64, y, "Animals Killed:");
    y += 16;
    unsigned int x = 64;

    for (int i = 0; i < whales_drawn; ++i) {
      icon_whale->draw(graphics, x, y);

      x += 32;
      if (x > 544) {
        x = 64;
        y += 16;
      }
    }

    for (int i = 0; i < fish_drawn; ++i) {
      icon_fish->draw(graphics, x, y);

      x += 16;
      if (x > 560) {
        x = 64;
        y += 16;
      }
    }

    y += 32;
  }

  if (text_drawn) {
    text->draw(graphics, 64, y, boost::str(boost::format("Total Damage: $% 9u") % damage));
    text->draw(graphics, 64, y + 32, "Q: Play again");
    text->draw(graphics, 64, y + 48, "E: Main Menu");
    text->draw(graphics, 64, y + 64, "Esc: Quit");
  }
}

Screen* GameOverScreen::next_screen() {
  switch (choice) {
    case REPLAY: return new GameScreen();
    case MENU: return new TitleScreen();
    case QUIT: return NULL;
  }
}

std::string GameOverScreen::get_music_track() {
  return "";
}

void GameOverScreen::set_scores(unsigned int total_damage, unsigned int whales_killed, unsigned int fish_killed) {
  damage = total_damage;
  whales = whales_killed;
  fish = fish_killed;
}

