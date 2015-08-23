#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

#include "sprite.h"
#include "water_obj.h"

class Audio;
class Graphics;

class Tanker : public WaterObject {
  public:

    Tanker(Graphics& graphics, unsigned int x, unsigned int y);

    void update(boost::shared_ptr<Map> map, unsigned int elapsed);
    void draw(Graphics& graphics);

    void start_moving(Direction dir);
    void start_leaking(Audio& audio);
    void boost(Audio& audio);

    unsigned int x_smoke();
    unsigned int y_smoke();

    bool is_leaking() { return leak_timer > 0; }
    bool is_boosting() { return boost_timer > 0; }

    unsigned int barrel_count() { return barrels; }
    unsigned int lawyer_count() { return lawyers; }
    unsigned int celeb_count() { return celebs; }

    void add_barrel() { barrels++; }
    void add_lawyer() { lawyers++; }
    void add_celeb() { celebs++; }

  private:

    unsigned int barrels, lawyers, celebs;
    int leak_timer, boost_timer;
    std::map<Direction, boost::shared_ptr<Sprite>> sprites;

    unsigned int x_draw();
    unsigned int y_draw();
};
