#pragma once

#include <map>
#include <vector>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

class Graphics;
class Sprite;

class Map {
  public:

    Map(Graphics& graphics);

    static const unsigned int rows = 30;
    static const unsigned int cols = 40;

    void draw(Graphics& graphics);
    unsigned int update(unsigned int elapsed);

    unsigned int dump_oil(unsigned int x, unsigned int y);
    void clean(unsigned int x, unsigned int y);

    bool sailable(unsigned int x, unsigned int y);
    bool is_oil(unsigned int x, unsigned int y);
    bool is_water(unsigned int x, unsigned int y);

  private:

    void init_sprites(Graphics& graphics);
    unsigned int spread_oil(unsigned int elapsed);

    enum TileType { WATER, OIL, LAND };

    std::vector<std::vector<TileType>> tiles;
    std::map<TileType, boost::shared_ptr<Sprite>> sprites;
};
