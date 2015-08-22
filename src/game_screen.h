#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

#include "map.h"
#include "screen.h"
#include "tanker.h"
#include "text.h"

class GameScreen : public Screen {
  public:

    void init(Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track();

  private:

    void spawn_boat(Graphics& graphics);
    void spawn_whale(Graphics& graphics);
    void spawn_fish(Graphics& graphics);

    typedef std::vector<boost::shared_ptr<WaterObject>> ObjectSet;

    boost::shared_ptr<Map> map;
    boost::shared_ptr<Tanker> tanker;
    boost::shared_ptr<Text> text;
    ObjectSet objects;

    unsigned int damage;
    int pr, spawn_timer;
};
