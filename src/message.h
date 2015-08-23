#pragma once

#include <queue>
#include <string>

#include <boost/shared_ptr.hpp>

#include "sprite.h"
#include "text.h"

class Graphics;

class Message {
  public:
    Message(Graphics& graphics);

    void update(unsigned int elapsed);
    void draw(Graphics& graphics);

    void show(std::string text);
    void dismiss();

  private:

    int timer;
    std::queue<std::string> messages;
    boost::shared_ptr<Text> text;
    boost::shared_ptr<Sprite> box, mouth;

};
