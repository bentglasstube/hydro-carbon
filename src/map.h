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

    void draw(Graphics& graphics);
    void update(unsigned int elapsed);

  private:

    void init_sprites(Graphics& graphics);
    void spread_oil();
    void spread_fire();

    enum TileType { WATER, OIL, LAND };

    std::vector<std::vector<TileType>> tiles;
    std::map<TileType, boost::shared_ptr<Sprite>> sprites;
};
