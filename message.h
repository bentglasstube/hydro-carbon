#pragma once

#include <queue>
#include <string>

#include <memory>

#include "sprite.h"
#include "text.h"

class Graphics;

class Message {
  public:
    Message(Graphics& graphics);

    void update(int elapsed);
    void draw(Graphics& graphics);

    void show(std::string text);
    void dismiss();

  private:

    int timer;
    std::queue<std::string> messages;
    std::shared_ptr<Text> text;
    std::shared_ptr<Sprite> box, mouth;

};
