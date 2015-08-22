#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

#include "sprite.h"
#include "water_obj.h"

class Graphics;

class Tanker : public WaterObject {
  public:

    Tanker(Graphics& graphics, unsigned int x, unsigned int y);

    void update(boost::shared_ptr<Map> map, unsigned int elapsed);
    void draw(Graphics& graphics);
    void start_moving(Direction dir);

    const int value() { return 0; }

    void start_leaking();
    void boost();

    bool is_leaking() { return leak_timer > 0; }
    bool is_boosting() { return boost_timer > 0; }

    unsigned int barrel_count() { return barrels; }
    unsigned int lawyer_count() { return lawyers; }
    unsigned int celeb_count() { return celebs; }

    void add_barrel() { barrels++; }
    void add_lawyer() { lawyers++; }
    void add_celeb() { celebs++; }

    unsigned int x_behind() { return facing == LEFT ? x + 1 : facing == RIGHT ? x - 1 : x; }
    unsigned int y_behind() { return facing == UP ? y + 1 : facing == DOWN ? y - 1 : y; }

  private:

    unsigned int barrels, lawyers, celebs;
    int leak_timer, boost_timer;
    std::map<Direction, boost::shared_ptr<Sprite>> sprites;
};
