#pragma once

#include <string>

#include "graphics.h"

class Text {

  public:

    enum Alignment { LEFT, CENTER, RIGHT };

    Text(Graphics& graphics);

    void draw(Graphics& graphics, int x, int y, const std::string& text, Alignment alignment=LEFT);

};

