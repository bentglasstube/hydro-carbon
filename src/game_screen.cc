#include "game_screen.h"

#include <boost/format.hpp>

#include "boat.h"
#include "fish.h"
#include "input.h"
#include "whale.h"

namespace {
  const int starting_pr = 63999;
  const int spawn_interval = 10000;
}

void GameScreen::init(Graphics& graphics) {
  map.reset(new Map(graphics));
  tanker.reset(new Tanker(graphics, 1, 7));

  objects = ObjectSet();

  text.reset(new Text(graphics));
  face.reset(new MultiSprite(graphics, "ui", 0, 0, 16, 16, 4, 2));

  damage = 0;
  pr = starting_pr;

  spawn_timer = spawn_interval;

  spawn_boat(graphics);
  spawn_boat(graphics);
}

bool GameScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  spawn_timer -= elapsed;
  if (spawn_timer <= 0) {
    spawn_timer += spawn_interval;

    int r = rand() % 8;
    if (r < 1) spawn_whale(graphics);
    else if (r < 4) spawn_fish(graphics);
    else spawn_boat(graphics);
  }

  if (!tanker->is_moving()) {
    if (input.key_pressed_or_held(SDLK_a)) {
      if (map->sailable(tanker->x_pos() - 1, tanker->y_pos())) tanker->start_moving(Tanker::LEFT);
    } else if (input.key_pressed_or_held(SDLK_d)) {
      if (map->sailable(tanker->x_pos() + 1, tanker->y_pos())) tanker->start_moving(Tanker::RIGHT);
    } else if (input.key_pressed_or_held(SDLK_w)) {
      if (map->sailable(tanker->x_pos(), tanker->y_pos() - 1)) tanker->start_moving(Tanker::UP);
    } else if (input.key_pressed_or_held(SDLK_s)) {
      if (map->sailable(tanker->x_pos(), tanker->y_pos() + 1)) tanker->start_moving(Tanker::DOWN);
    }
  }

  if (input.key_pressed(SDLK_ESCAPE)) return false;

  if (input.key_pressed(SDLK_SPACE)) tanker->start_leaking();

  tanker->update(map, elapsed);
  damage += map->update(elapsed);

  ObjectSet::iterator i = objects.begin();
  while (i != objects.end()) {
    boost::shared_ptr<WaterObject> obj = *i;
    obj->update(map, elapsed);

    boost::shared_ptr<Boat> boat = boost::dynamic_pointer_cast<Boat>(obj);
    if (boat && map->is_oil(boat->x_pos(), boat->y_pos())) pr -= elapsed;

    if (obj->is_touching(tanker->x_pos(), tanker->y_pos())) {
      int value = obj->value();
      if (value < 0) {
        pr -= value;
      } else {
        damage += value;
      }

      objects.erase(i);
    } else {
      ++i;
    }
  }

  if (tanker->is_leaking()) damage += map->dump_oil(tanker->x_behind(), tanker->y_behind());

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  map->draw(graphics);
  tanker->draw(graphics);

  for (ObjectSet::iterator i = objects.begin(); i != objects.end(); ++i) {
    (*i)->draw(graphics);
  }

  text->draw(graphics, 624, 16, boost::str(boost::format("Damages $% 9u") % damage), Text::RIGHT);

  int n = 7 - pr / 8000;
  if (n < 0) n = 0;
  if (n > 7) n = 7;
  face->draw(graphics, 608, 32, n);

  text->draw(graphics, 608, 32, "Opinion: ", Text::RIGHT);
}

Screen* GameScreen::next_screen() {
  return NULL;
}

std::string GameScreen::get_music_track() {
  return "";
}

void GameScreen::spawn_boat(Graphics& graphics) {
  switch (rand() % 3) {
    case 0:
      objects.push_back(boost::shared_ptr<Boat>(new Boat(graphics, 0, rand() % 20 + 10, Boat::RIGHT)));
      break;

    case 1:
      objects.push_back(boost::shared_ptr<Boat>(new Boat(graphics, 39, rand() % 20 + 10, Boat::LEFT)));
      break;

    case 2:
      objects.push_back(boost::shared_ptr<Boat>(new Boat(graphics, 29, rand() % 40, Boat::UP)));
      break;
  }
}

void GameScreen::spawn_whale(Graphics& graphics) {
  unsigned int x = rand() % 40;
  unsigned int y = rand() % 30;

  if (map->is_water(x, y)) {
    objects.push_back(boost::shared_ptr<Whale>(new Whale(graphics, x, y)));
    // TODO check if first whale and alert
  }
}

void GameScreen::spawn_fish(Graphics& graphics) {
  unsigned int x = rand() % 40;
  unsigned int y = rand() % 30;

  if (map->is_water(x, y)) {
    objects.push_back(boost::shared_ptr<Fish>(new Fish(graphics, x, y)));
    // TODO Check if first fish and alert
  }

}
