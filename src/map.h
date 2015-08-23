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
    bool is_land(unsigned int x, unsigned int y);

  private:

    unsigned int spread_oil(unsigned int elapsed);

    enum TileType { WATER, OIL, LAND };
    enum EdgeType { NW, N, NE, W, E, SW, S, SE };
    enum BeachType { INNER_LEFT, INNER_RIGHT, OUTER_LEFT, OUTER_MIDDLE, OUTER_RIGHT };

    std::vector<std::vector<TileType>> tiles;

    std::map<TileType,  boost::shared_ptr<Sprite>> tile_sprites;
    std::map<EdgeType,  boost::shared_ptr<Sprite>> edge_sprites;
    std::map<BeachType, boost::shared_ptr<Sprite>> beach_sprites;
};
