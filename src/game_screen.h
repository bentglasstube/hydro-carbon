#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

#include "boat.h"
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

    typedef std::vector<boost::shared_ptr<Boat>> BoatSet;

    boost::shared_ptr<Map> map;
    boost::shared_ptr<Tanker> tanker;
    BoatSet boats;
};
