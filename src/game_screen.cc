#include "game_screen.h"

#include <boost/format.hpp>

#include "input.h"

namespace {
  const int starting_pr = 60000;
  const int boat_spawn_interval = 30000;
}

void GameScreen::init(Graphics& graphics) {
  map.reset(new Map(graphics));
  tanker.reset(new Tanker(graphics, 1, 7));
  text.reset(new Text(graphics));

  boats = BoatSet();

  spawn_boat(graphics);
  spawn_boat(graphics);

  damage = 0;
  pr = starting_pr;

  boat_spawn_timer = boat_spawn_interval;
}

bool GameScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  boat_spawn_timer -= elapsed;
  if (boat_spawn_timer <= 0) {
    boat_spawn_timer += boat_spawn_interval;
    spawn_boat(graphics);
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

  if (input.key_pressed(SDLK_SPACE)) {
    tanker->toggle_leaking();
  }

  tanker->update(map, elapsed);
  damage += map->update(elapsed);

  for (BoatSet::iterator i = boats.begin(); i != boats.end(); ++i) {
    (*i)->update(map, elapsed);
    if ((*i)->is_cleaning()) {
      pr -= elapsed;
    }
  }

  if (tanker->is_leaking()) damage += map->dump_oil(tanker->x_behind(), tanker->y_behind());

  return true;
}

void GameScreen::draw(Graphics& graphics) {
  map->draw(graphics);
  tanker->draw(graphics);

  for (BoatSet::iterator i = boats.begin(); i != boats.end(); ++i) {
    (*i)->draw(graphics);
  }

  text->draw(graphics, 624, 16, boost::str(boost::format("Damages $% 9u") % damage), Text::RIGHT);
  text->draw(graphics, 624, 32, boost::str(boost::format("PR % 5u") % pr), Text::RIGHT);
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
      boats.push_back(boost::shared_ptr<Boat>(new Boat(graphics, 0, rand() % 20 + 10, Boat::RIGHT)));
      break;

    case 1:
      boats.push_back(boost::shared_ptr<Boat>(new Boat(graphics, 39, rand() % 20 + 10, Boat::LEFT)));
      break;

    case 2:
      boats.push_back(boost::shared_ptr<Boat>(new Boat(graphics, 29, rand() % 40, Boat::UP)));
      break;
  }
}
