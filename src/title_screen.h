#pragma once

#include <boost/scoped_ptr.hpp>

#include "backdrop.h"
#include "screen.h"
#include "text.h"

class TitleScreen : public Screen {
  public:

    void init(Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track() { return ""; }

  private:

    boost::scoped_ptr<Backdrop> backdrop;
    boost::scoped_ptr<Text> text;
};
