#pragma once

#include <map>
#include <vector>

#include <memory>

class Graphics;
class Sprite;

class Map {
  public:

    Map(Graphics& graphics);

    static const int rows = 30;
    static const int cols = 40;

    void draw(Graphics& graphics);
    int update(int elapsed);

    int dump_oil(int x, int y);
    void clean(int x, int y);

    bool sailable(int x, int y);
    bool is_oil(int x, int y);
    bool is_water(int x, int y);
    bool is_land(int x, int y);

  private:

    int spread_oil(int elapsed);

    enum TileType { WATER, OIL, LAND };
    enum EdgeType { NW, N, NE, W, E, SW, S, SE };
    enum BeachType { INNER_LEFT, INNER_RIGHT, OUTER_LEFT, OUTER_MIDDLE, OUTER_RIGHT };

    std::vector<std::vector<TileType>> tiles;

    std::map<TileType,  std::shared_ptr<Sprite>> tile_sprites;
    std::map<EdgeType,  std::shared_ptr<Sprite>> edge_sprites;
    std::map<BeachType, std::shared_ptr<Sprite>> beach_sprites;
};
