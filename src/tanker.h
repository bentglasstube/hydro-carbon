#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

#include "sprite.h"
#include "water_obj.h"

class Audio;
class Graphics;

class Tanker : public WaterObject {
  public:

    Tanker(Graphics& graphics, int x, int y);

    void update(boost::shared_ptr<Map> map, int elapsed);
    void draw(Graphics& graphics);

    void start_moving(Direction dir);
    void start_leaking(Audio& audio);
    void boost(Audio& audio);

    int x_smoke();
    int y_smoke();

    bool is_leaking() { return leak_timer > 0; }
    bool is_boosting() { return boost_timer > 0; }

    int barrel_count() { return barrels; }
    int lawyer_count() { return lawyers; }
    int celeb_count() { return celebs; }

    void add_barrel() { barrels++; }
    void add_lawyer() { lawyers++; }
    void add_celeb() { celebs++; }

  private:

    int barrels, lawyers, celebs;
    int leak_timer, boost_timer;
    std::map<Direction, boost::shared_ptr<Sprite>> sprites;

    int x_draw();
    int y_draw();
};
