#include "game_screen.h"

#include <boost/format.hpp>

#include "animated_sprite.h"
#include "audio.h"
#include "barrel.h"
#include "boat.h"
#include "fish.h"
#include "game_over_screen.h"
#include "ghost.h"
#include "input.h"
#include "smoke.h"
#include "whale.h"

#define ISA(obj, type) boost::dynamic_pointer_cast<type>(obj)

namespace {
  const int starting_pr = 63999;
  const int spawn_interval = 15000;
  const int smoke_interval = 250;

  const unsigned int hud_barrel = 8;
  const unsigned int hud_lawyer = 9;
  const unsigned int hud_celeb = 10;

  const unsigned int fish_value = 500;
  const unsigned int whale_value = 1500;
  const unsigned int boat_value = 1000;
}

std::map<GameScreen::Tips, std::string> GameScreen::tips = {
  { GameScreen::OIL,      "Sir!\n"
                          "We've spotted an extra barrel of oil in the water. Drive the\n"
                          "ship over it to collect it." },
  { GameScreen::BOAT,     "All hands on deck!\n"
                          "We have spotted one of the environmentalists' boats.  They will\n"
                          "Do their best to clean up the oil and make the public aware of\n"
                          "our impact.  You can ignore them or crash into them to take them\n"
                          "out of the picture..." },
  { GameScreen::FISH,     "Avast!\n"
                          "There are seagulls gathering in the distance, which means there\n"
                          "is food nearby.   Navgiate toward them and we can rid ourselves\n"
                          "of that piscene nuissance." },
  { GameScreen::WHALE,    "Thar she blows!\n"
                          "The menace of all seafarers, a whale, has been spotted!  Try to\n"
                          "track it and destroy the devilbeast as soon as you can!" },
  { GameScreen::CLEANUP,  "Anchors aweigh!\n"
                          "The tree huggers have found our spilled oil and are attempting\n"
                          "to clean it up.  While doing so, they are spreading the news\n"
                          "about the spill to turn the public against us.  Take care of\n"
                          "them before they get us stuck with a lawsuit." },
  { GameScreen::CRASH,    "Damage report!\n"
                          "We have smashed into one of the hippies' boats!  That will\n"
                          "teach them to mess with us!  It seems that the public knows\n"
                          "what we did though, so be careful." },
  { GameScreen::OPINION,  "Abandon Ship!\n"
                          "The media has turned the masses against us.  They are likely\n"
                          "to bring a court case against us soon, forcing us to shore\n"
                          "for who knows how long.  Time to get out of here." }
};

std::vector<std::string> GameScreen::tutorial = {
  "Ahoy!\n"
  "Welcome aboard, Captain.  Our job today is to desrtoy as much\n"
  "terrible nature as possible by dumping oil into the water.  I\n"
  "will show you the ropes so we can deal as much damage as\n"
  "possible.  Press space when you are done with this message, or\n"
  "you can just wait for it to go away.",

  "Control the oil tanker with WASD.  If you stop pressing the\n"
  "keys, the tanker will stop, too.  We started the day with five\n"
  "barrels of oil, which you can see in the top left of the\n"
  "screen.  These barrels can be used for two different things.\n"
  "By pressing Q, you can dump a barrel into the ocean, causing\n"
  "environmental damage.",

  "By presseing E, you can use the oil to give the engine an extra\n"
  "bit of juice for a short period.  Use these barrels wisely, but\n"
  "don't be too stingy, as I'm sure we'll find more around.",

  "Various different things might be found in the nearby waters.\n"
  "I will give you hints about each thing as we come across them.\n"
  "The main thing you need to worry about (aside from destroying\n"
  "the stupid environment) is the public.",

  "The public's feelings about us is shown in the top right corner\n"
  "of the screen.  When the public gets too upset with our\n"
  "destruction, the government will be forced to act and we'll\n"
  "have to stop to deal with any lawsuits or what have you.",

  "That's about all there is to it.  If you need to hear these\n"
  "words of wisdom again, just hit T.\n\n"
  "Good luck, sir!",
};

void GameScreen::init(Graphics& graphics) {
  map.reset(new Map(graphics));
  tanker.reset(new Tanker(graphics, 1, 10));

  objects = ObjectSet();
  particles = ParticleSet();

  text.reset(new Text(graphics));
  hud.reset(new MultiSprite(graphics, "ui", 0, 0, 16, 16, 4, 3));
  msg.reset(new Message(graphics));

  damage = whales = fish = 0;
  pr = starting_pr;

  spawn_timer = spawn_interval / 2;
  smoke_timer = smoke_interval;

  msg->show("Press T for a tutorial or space to dismiss this.");
}

bool GameScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  spawn_timer -= elapsed;
  if (spawn_timer <= 0) {
    spawn_timer += spawn_interval;

    int r = rand() % 16;
    if (r < 1) spawn_whale(graphics, audio);
    else if (r < 4) spawn_fish(graphics, audio);
    else if (r < 8) spawn_boat(graphics);
    else spawn_barrel(graphics);
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

  if (input.key_pressed(SDLK_q)) {
    tanker->start_leaking(audio);
  }

  if (input.key_pressed(SDLK_e)) {
    tanker->boost(audio);
  }

  if (input.key_pressed(SDLK_t)) {
    msg->dismiss();
    for (std::vector<std::string>::iterator i = GameScreen::tutorial.begin(); i != GameScreen::tutorial.end(); ++i) msg->show(*i);
  }

  if (input.key_pressed(SDLK_SPACE)) msg->dismiss();

  tanker->update(map, elapsed);
  damage += map->update(elapsed);

  ObjectSet::iterator i = objects.begin();
  while (i != objects.end()) {
    boost::shared_ptr<WaterObject> obj = *i;
    obj->update(map, elapsed);

    bool erase = false;

    if (map->is_oil(obj->x_pos(), obj->y_pos())) {
      if (ISA(obj, Boat)) {
        pr -= elapsed;
        maybe_show_message(CLEANUP);
      }

      if (ISA(obj, Whale)) {
        whales++;
        damage += whale_value;
        add_ghost(graphics, audio, obj);
        erase = true;
      }

      if (ISA(obj, Fish)) {
        fish++;
        damage += fish_value;
        add_ghost(graphics, audio, obj);
        erase = true;
      }
    }

    if (obj->is_touching(tanker->x_pos(), tanker->y_pos())) {
      if (ISA(obj, Boat)) {
        pr -= boat_value;
        audio.play_sample("crash");
        maybe_show_message(CRASH);
        erase = true;
      }

      if (ISA(obj, Barrel)) {
        tanker->add_barrel();
        audio.play_sample("pickup");
        erase = true;
      }
    }

    if (erase) objects.erase(i);
    else ++i;
  }

  ParticleSet::iterator j = particles.begin();
  while (j != particles.end()) {
    if ((*j)->update(elapsed)) {
      ++j;
    } else {
      particles.erase(j);
    }
  }

  msg->update(elapsed);

  if (tanker->is_leaking()) {
    damage += map->dump_oil(tanker->x_pos(), tanker->y_pos());
    // TODO particles
  }

  smoke_timer -= elapsed * (tanker->is_boosting() ? 2 : 1);
  if (smoke_timer < 0) {
    particles.push_back(boost::shared_ptr<Particle>(new Smoke(graphics, tanker->x_smoke(), tanker->y_smoke(), tanker->is_boosting())));
    smoke_timer += smoke_interval;
  }

  return pr > 0;
}

void GameScreen::draw(Graphics& graphics) {
  map->draw(graphics);

  for (ObjectSet::iterator i = objects.begin(); i != objects.end(); ++i) {
    (*i)->draw(graphics);
  }

  tanker->draw(graphics);

  for (ParticleSet::iterator i = particles.begin(); i != particles.end(); ++i) {
    (*i)->draw(graphics);
  }

  msg->draw(graphics);

  draw_power_up(graphics, 16, hud_barrel, tanker->barrel_count());
  draw_power_up(graphics, 112, hud_lawyer, tanker->lawyer_count());
  draw_power_up(graphics, 208, hud_celeb, tanker->celeb_count());

  text->draw(graphics, 608, 0, boost::str(boost::format("Damage $% 9u") % damage), Text::RIGHT);

  int n = 7 - pr / 8000;
  if (n < 0) n = 0;
  if (n > 7) n = 7;
  hud->draw(graphics, 624, 0, n);

  if (n == 7) maybe_show_message(OPINION);
}

Screen* GameScreen::next_screen() {
  GameOverScreen* screen = new GameOverScreen();
  screen->set_scores(damage, whales, fish);
  return screen;
}

std::string GameScreen::get_music_track() {
  return "funkyseas";
}

void GameScreen::spawn_boat(Graphics& graphics) {
  switch (rand() % 3) {
    case 0:
      objects.push_back(boost::shared_ptr<WaterObject>(new Boat(graphics, 0, rand() % (Map::rows - 10) + 10, Boat::RIGHT)));
      break;

    case 1:
      objects.push_back(boost::shared_ptr<WaterObject>(new Boat(graphics, Map::cols - 1, rand() % (Map::rows - 10) + 10, Boat::LEFT)));
      break;

    case 2:
      objects.push_back(boost::shared_ptr<WaterObject>(new Boat(graphics, rand() % Map::cols, Map::rows - 1, Boat::UP)));
      break;
  }

  maybe_show_message(BOAT);
}

void GameScreen::spawn_whale(Graphics& graphics, Audio& audio) {
  unsigned int x = rand() % Map::cols;
  unsigned int y = rand() % (Map::rows - 10) + 10;

  if (map->is_water(x, y)) {
    objects.push_back(boost::shared_ptr<WaterObject>(new Whale(graphics, x, y)));
    maybe_show_message(WHALE);
    audio.play_sample("whale");
  }
}

void GameScreen::spawn_fish(Graphics& graphics, Audio& audio) {
  unsigned int x = rand() % Map::cols;
  unsigned int y = rand() % (Map::rows - 10) + 10;

  if (map->is_water(x, y)) {
    objects.push_back(boost::shared_ptr<WaterObject>(new Fish(graphics, x, y)));
    maybe_show_message(FISH);
    audio.play_sample("gulls");
  }
}

void GameScreen::spawn_barrel(Graphics& graphics) {
  unsigned int x = rand() % Map::cols;
  unsigned int y = rand() % (Map::rows - 10) + 10;

  if (map->sailable(x, y)) {
    objects.push_back(boost::shared_ptr<WaterObject>(new Barrel(graphics, x, y)));
    maybe_show_message(OIL);
  }
}

void GameScreen::add_ghost(Graphics& graphics, Audio& audio, boost::shared_ptr<WaterObject> obj) {
  particles.push_back(boost::shared_ptr<Particle>(new Ghost(graphics, 16 * obj->x_pos(), 16 * obj->y_pos())));
  audio.play_sample("ghost");
}

void GameScreen::draw_power_up(Graphics& graphics, unsigned int x, unsigned int icon, unsigned int count) {
  if (count > 5) {
    hud->draw(graphics, x, 0, icon);
    text->draw(graphics, x + 16, 0, boost::str(boost::format("x%u") % count));
  } else {
    for (int i = 0; i < count; i++) hud->draw(graphics, x + 16 * i, 0, icon);
  }
}

void GameScreen::maybe_show_message(Tips tip) {
  if (shown.count(tip) == 0) {
    msg->show(tips[tip]);
    shown[tip] = true;
  }
}
