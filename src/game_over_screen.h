#pragma once

#include <boost/shared_ptr.hpp>

#include "backdrop.h"
#include "screen.h"
#include "sprite.h"
#include "text.h"

class Graphics;

class GameOverScreen : public Screen {
  public:

    void init(Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track();

    void set_scores(unsigned int total_damage, unsigned int whales_killed, unsigned int fish_killed);

  private:

    enum Choice { REPLAY, MENU, QUIT };

    Choice choice;
    unsigned int damage, whales, fish;
    unsigned int whales_drawn, fish_drawn;
    bool text_drawn;
    int timer;

    boost::shared_ptr<Backdrop> backdrop;
    boost::shared_ptr<Text> text;
    boost::shared_ptr<Sprite> title, icon_whale, icon_fish;
};
