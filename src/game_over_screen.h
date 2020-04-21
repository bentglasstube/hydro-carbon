#pragma once

#include <memory>

#include "backdrop.h"
#include "screen.h"
#include "sprite.h"
#include "text.h"

class Graphics;

class GameOverScreen : public Screen {
  public:

    void init(Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track();

    void set_scores(int total_damage, int whales_killed, int fish_killed);

  private:

    enum Choice { REPLAY, MENU, QUIT };
    enum Phase { TITLE, KILLS, DAMAGE, SCORES, OPTIONS };

    struct HighScore {
      char         initials[3];
      int score;
    };

    void next_phase(Audio& audio);

    Choice choice;
    Phase phase;
    int damage, whales, fish;
    int whales_drawn, fish_drawn;

    int place, initials_pos;

    int timer;
    HighScore top_scores[10];

    std::shared_ptr<Backdrop> backdrop;
    std::shared_ptr<Text> text;
    std::shared_ptr<Sprite> icon_whale, icon_fish;
};
