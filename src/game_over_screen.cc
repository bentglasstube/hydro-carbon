#include "game_over_screen.h"

#include <stdio.h>
#include <string.h>

#include <boost/format.hpp>

#include "audio.h"
#include "input.h"
#include "game_screen.h"
#include "graphics.h"
#include "title_screen.h"

namespace {
  const int interval = 250;
}

void GameOverScreen::init(Graphics& graphics) {
  backdrop.reset(new Backdrop(graphics, "paper"));
  text.reset(new Text(graphics));

  icon_whale.reset(new Sprite(graphics, "ui", 0, 48, 32, 16));
  icon_fish.reset(new Sprite(graphics, "ui", 32, 48, 16, 16));

  phase = TITLE;
  fish_drawn = whales_drawn = 0;
  place = 99;
  initials_pos = 0;
  timer = 0;

  FILE* fd = fopen("content/scores.txt", "r");
  if (fd) {
    for (int i = 0; i < 10; ++i) {
      char initials[4];
      int score;

      int count = fscanf(fd, "%3s%u\n", initials, &score);
      if (count < 2) break;

      if (damage > score && place > 10) {
        fprintf(stderr, "Congrats, %u place\n", i);
        place = i;
        strcpy(top_scores[i].initials, "___");
        top_scores[i].score = damage;
        ++i;
      }

      // bounds check in case bottom score was bumped
      if (i < 10) {
        strcpy(top_scores[i].initials, initials);
        top_scores[i].score = score;
      }
    }
    fclose(fd);
  } else {
    fprintf(stderr, "Unable to read high score file\n");
  }
}

bool GameOverScreen::update(Input& input, Audio& audio, Graphics&, int elapsed) {
  timer -= elapsed;

  if (timer < 0) {
    timer += interval;

    if (phase == KILLS) {
      if (whales > 0) {
        whales_drawn++;
        audio.play_sample("kill");
        if (--whales == 0) timer += 2 * interval;
      } else if (fish > 0) {
        fish_drawn++;
        audio.play_sample("kill");
        if (--fish == 0) timer += 2 * interval;
      } else {
        next_phase(audio);
      }
    } else if (phase != SCORES) {
      next_phase(audio);
    }
  }

  if (phase == OPTIONS) {

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

  } else if (phase == KILLS) {
    if (input.any_pressed()) {
      whales_drawn += whales;
      fish_drawn += fish;
      whales = fish = 0;
      next_phase(audio);
    }

  } else if (phase == SCORES) {

    if (place < 10 && initials_pos < 3) {
      // horrible hack because of how I handle input :(
      for (int i = SDLK_a; i < SDLK_z; ++i) {
        if (input.key_pressed(i)) {
          top_scores[place].initials[initials_pos] = i - SDLK_a + 'A';
          ++initials_pos;
          break;
        }
      }

      if (initials_pos == 3) {
        FILE* fd = fopen("content/scores.txt", "w");
        if (fd) {
          for (int i = 0; i < 10; ++i) {
            fprintf(fd, "%3s %u\n", top_scores[i].initials, top_scores[i].score);
          }
          fclose(fd);
        } else {
          fprintf(stderr, "Unable to write scores to file\n");
        }
      }
    } else {
      next_phase(audio);
    }
  }

  return true;
}

void GameOverScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);

  if (phase >= TITLE) text->draw(graphics, 48, 80, "Environmental Impact Report");

  int y = 112;

  if (phase >= KILLS) {
    text->draw(graphics, 48, y, "Animals Killed:");
    y += 16;
    int x = 48;

    for (int i = 0; i < whales_drawn; ++i) {
      icon_whale->draw(graphics, x, y);

      x += 32;
      if (x > 544) {
        x = 48;
        y += 16;
      }
    }

    for (int i = 0; i < fish_drawn; ++i) {
      icon_fish->draw(graphics, x, y);

      x += 16;
      if (x > 560) {
        x = 48;
        y += 16;
      }
    }

    y += 32;
  }

  if (phase >= DAMAGE) {
    text->draw(graphics, 48, y, boost::str(boost::format("Total Damage: $% 9u") % damage));
    y += 32;
  }

  if (phase >= SCORES) {
    text->draw(graphics, 48, y, "Most Wanted:");
    for (int i = 0; i < 5; ++i) {
      text->draw(graphics,  48, y + 16 * i + 16, boost::str(boost::format("%2u. %3s   $%9u") % (i + 1) % top_scores[i].initials % top_scores[i].score));
      text->draw(graphics, 320, y + 16 * i + 16, boost::str(boost::format("%2u. %3s   $%9u") % (i + 6) % top_scores[i + 5].initials % top_scores[i + 5].score));

    }

    y += 112;

    if (place < 10) {
      text->draw(graphics, 48, y,
          "Congratulations, you are one of the most horrible people we\n"
          "have ever encountered.  Please acknowledge receipt of this\n"
          "report by entering your initials above.\n"
      );

      y += 64;
    }

  }

  if (phase >= OPTIONS) {
    text->draw(graphics, 48, y, "Q: Play again     E: Main Menu     Esc: Quit");
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

void GameOverScreen::set_scores(int total_damage, int whales_killed, int fish_killed) {
  damage = total_damage;
  whales = whales_killed;
  fish = fish_killed;
}

void GameOverScreen::next_phase(Audio& audio) {
  if (phase == OPTIONS) return;

  phase = static_cast<Phase>(phase + 1);
  timer += interval * 2;
  audio.play_sample("boom");
}
