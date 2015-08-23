#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

#include "map.h"
#include "message.h"
#include "multi_sprite.h"
#include "particle.h"
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

    enum Tips { OIL, BOAT, FISH, WHALE, CLEANUP, CRASH, OPINION, POLICE };

    static std::map<Tips, std::string> tips;
    static std::vector<std::string> tutorial;

    void spawn_boat(Graphics& graphics);
    void spawn_police(Graphics& Graphics, Audio& audio);

    void spawn_whale(Graphics& graphics, Audio& audio);
    void spawn_fish(Graphics& graphics, Audio& audio);
    void spawn_barrel(Graphics& graphics);

    void add_ghost(Graphics& graphics, Audio& audio, boost::shared_ptr<WaterObject> obj);

    void draw_power_up(Graphics& graphics, unsigned int x, unsigned int icon, unsigned int count);
    void maybe_show_message(Tips tip);

    typedef std::vector<boost::shared_ptr<WaterObject>> ObjectSet;
    typedef std::vector<boost::shared_ptr<Particle>> ParticleSet;

    boost::shared_ptr<Map> map;
    boost::shared_ptr<Tanker> tanker;
    ObjectSet objects;
    ParticleSet particles;

    boost::shared_ptr<Text> text;
    boost::shared_ptr<MultiSprite> hud;
    boost::shared_ptr<Message> msg;

    unsigned int damage, whales, fish;
    int pr, spawn_timer, smoke_timer;

    std::map<Tips, bool> shown;
};
