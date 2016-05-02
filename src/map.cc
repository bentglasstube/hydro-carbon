#include "map.h"

#include "animated_sprite.h"
#include "graphics.h"
#include "sprite.h"

Map::Map(Graphics& graphics) {
  tile_sprites[Map::WATER] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 0,  0, 16, 16, 8));
  tile_sprites[Map::OIL]   = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 0, 16, 16, 16, 8));
  tile_sprites[Map::LAND]  = boost::shared_ptr<Sprite>(new Sprite(graphics, "map", 64, 128, 16, 16));

  edge_sprites[Map::NW] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 0, 32, 16, 16, 4));
  edge_sprites[Map::NE] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 0, 48, 16, 16, 4));
  edge_sprites[Map::SW] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 0, 64, 16, 16, 4));
  edge_sprites[Map::SE] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 0, 80, 16, 16, 4));

  edge_sprites[Map::N] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 64, 32, 16, 16, 4));
  edge_sprites[Map::S] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 64, 48, 16, 16, 4));
  edge_sprites[Map::W] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 64, 64, 16, 16, 4));
  edge_sprites[Map::E] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 64, 80, 16, 16, 4));

  beach_sprites[Map::INNER_LEFT]   = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map",  0,  96, 16, 16, 4));
  beach_sprites[Map::INNER_RIGHT]  = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 64,  96, 16, 16, 4));
  beach_sprites[Map::OUTER_LEFT]   = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map",  0, 112, 16, 16, 4));
  beach_sprites[Map::OUTER_RIGHT]  = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map", 64, 112, 16, 16, 4));
  beach_sprites[Map::OUTER_MIDDLE] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "map",  0, 128, 16, 16, 4));

  tiles = std::vector<std::vector<TileType>>(rows, std::vector<TileType>(cols, Map::WATER));

  // TODO improve this garbage
  int cy = 6;
  for (int x = 0; x < cols; ++x) {
    for (int y = 0; y < cy; ++y) {
      tiles[y][x] = Map::LAND;
    }

    if (x % 2 == 1) {
      int d = rand() % 4;
      if (d == 0) cy--;
      if (d == 1) cy++;

      if (cy < 3) cy = 3;
      if (cy > 8) cy = 8;
    }
  }
}

void Map::draw(Graphics& graphics) {
  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      const int dx = 16 * x;
      const int dy = 16 * y;
      tile_sprites[tiles[y][x]]->draw(graphics, dx, dy);

      if (is_land(x, y)) {
        if (sailable(x, y + 1)) {
          if      (sailable(x - 1, y)) beach_sprites[Map::OUTER_LEFT]->draw(graphics, dx, dy);
          else if (sailable(x + 1, y)) beach_sprites[Map::OUTER_RIGHT]->draw(graphics, dx, dy);
          else                         beach_sprites[Map::OUTER_MIDDLE]->draw(graphics, dx, dy);
        } else if (sailable(x - 1, y + 1)) {
          beach_sprites[Map::INNER_LEFT]->draw(graphics, dx, dy);
        } else if (sailable(x + 1, y + 1)) {
          beach_sprites[Map::INNER_RIGHT]->draw(graphics, dx, dy);
        }
      }

      if (is_oil(x - 1, y - 1)) edge_sprites[Map::NW]->draw(graphics, dx, dy);
      if (is_oil(x + 1, y - 1)) edge_sprites[Map::NE]->draw(graphics, dx, dy);
      if (is_oil(x - 1, y + 1)) edge_sprites[Map::SW]->draw(graphics, dx, dy);
      if (is_oil(x + 1, y + 1)) edge_sprites[Map::SE]->draw(graphics, dx, dy);

      if (is_oil(x - 1, y)) edge_sprites[Map::W]->draw(graphics, dx, dy);
      if (is_oil(x + 1, y)) edge_sprites[Map::E]->draw(graphics, dx, dy);
      if (is_oil(x, y - 1)) edge_sprites[Map::N]->draw(graphics, dx, dy);
      if (is_oil(x, y + 1)) edge_sprites[Map::S]->draw(graphics, dx, dy);

    }
  }
}

int Map::update(int elapsed) {
  return spread_oil(elapsed);
}

int Map::dump_oil(int x, int y) {
  if (x >= cols || x < 0) return 0;
  if (y >= rows || y < 0) return 0;

  if (tiles[y][x] == Map::WATER) {
    tiles[y][x] = Map::OIL;
    return 100;
  } else {
    return 0;
  }
}

void Map::clean(int x, int y) {
  if (x >= cols || x < 0) return;
  if (y >= rows || y < 0) return;

  if (tiles[y][x] == Map::OIL) tiles[y][x] = Map::WATER;
}

bool Map::sailable(int x, int y) {
  if (x >= cols || x < 0) return false;
  if (y >= rows || y < 0) return false;
  return tiles[y][x] != Map::LAND;
}

bool Map::is_oil(int x, int y) {
  if (x >= cols || x < 0) return false;
  if (y >= rows || y < 0) return false;
  return tiles[y][x] == Map::OIL;
}

bool Map::is_water(int x, int y) {
  if (x >= cols || x < 0) return false;
  if (y >= rows || y < 0) return false;
  return tiles[y][x] == Map::WATER;
}

bool Map::is_land(int x, int y) {
  if (x >= cols || x < 0) return false;
  if (y >= rows || y < 0) return false;
  return tiles[y][x] == Map::LAND;
}

int Map::spread_oil(int elapsed) {
  int score = 0;

  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      if (tiles[y][x] == OIL) {
        if (elapsed >= rand() % 16384) {
          switch (rand() % 4) {
            case 0: score += dump_oil(x - 1, y); break;
            case 1: score += dump_oil(x + 1, y); break;
            case 2: score += dump_oil(x, y - 1); break;
            case 3: score += dump_oil(x, y + 1); break;
          }
        }
      }
    }
  }

  return score;
}
