#pragma once

#include <boost/scoped_ptr.hpp>

#include "map.h"
#include "screen.h"
#include "tanker.h"

class GameScreen : public Screen {
  public:

    void init(Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track();

  private:

    boost::scoped_ptr<Map> map;
    boost::scoped_ptr<Tanker> tanker;
};
