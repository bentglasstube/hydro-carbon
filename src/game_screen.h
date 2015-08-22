#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

#include "map.h"
#include "multi_sprite.h"
#include "screen.h"
#include "tanker.h"
#include "text.h"
#include "water_obj.h"

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
    void spawn_barrel(Graphics& graphics);

    void draw_power_up(Graphics& graphics, unsigned int x, unsigned int icon, unsigned int count);

    typedef std::vector<boost::shared_ptr<WaterObject>> ObjectSet;

    boost::shared_ptr<Map> map;
    boost::shared_ptr<Tanker> tanker;
    ObjectSet objects;

    boost::shared_ptr<Text> text;
    boost::shared_ptr<MultiSprite> hud;

    unsigned int damage, whales, fish;
    int pr, spawn_timer;
};
