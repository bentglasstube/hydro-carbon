#pragma once

#include <boost/scoped_ptr.hpp>

#include "screen.h"

class Text;

class TitleScreen : public Screen {
  public:

    void init(Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen() { return NULL; }
    std::string get_music_track() { return ""; }

  private:

    boost::scoped_ptr<Text> text;
};
