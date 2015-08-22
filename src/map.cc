#include "map.h"

#include "graphics.h"
#include "sprite.h"

namespace {
  const unsigned int rows = 30;
  const unsigned int cols = 40;
}

Map::Map(Graphics& graphics) {
  init_sprites(graphics);

  tiles = std::vector<std::vector<TileType>>(rows, std::vector<TileType>(cols, Map::WATER));

  // TODO improve this garbage
  int cy = 5;
  for (int x = 0; x < cols; ++x) {
    for (int y = 0; y < cy; ++y) {
      tiles[y][x] = Map::LAND;
    }

    if (x % 2 == 1) {
      int d = rand() % 4;
      if (d == 0) cy--;
      if (d == 1) cy++;

      if (cy < 2) cy = 2;
      if (cy > 7) cy = 7;
    }
  }
}

void Map::draw(Graphics& graphics) {
  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      sprites[tiles[y][x]]->draw(graphics, 16 * x, 16 * y);
    }
  }
}

void Map::update(unsigned int elapsed) {
  // TODO figure out chance of spreading fire and oil and shit
}

void Map::dump_oil(unsigned int x, unsigned int y) {
  if (x >= cols) return;
  if (y >= rows) return;

  if (tiles[y][x] == Map::WATER) tiles[y][x] = Map::OIL;
}

bool Map::sailable(unsigned int x, unsigned int y) {
  if (x >= cols) return false;
  if (y >= rows) return false;
  return tiles[y][x] != Map::LAND;
}

void Map::init_sprites(Graphics& graphics) {
  sprites[Map::WATER] = boost::shared_ptr<Sprite>(new Sprite(graphics, "map", 0, 0, 16, 16));
  sprites[Map::OIL] = boost::shared_ptr<Sprite>(new Sprite(graphics, "map", 16, 0, 16, 16));
  sprites[Map::LAND] = boost::shared_ptr<Sprite>(new Sprite(graphics, "map", 32, 0, 16, 16));
}

void Map::spread_oil() {
  // TODO spread oil around to adjacent blocks
}

void Map::spread_fire() {
  // TODO spread fire to nearby oil
}
