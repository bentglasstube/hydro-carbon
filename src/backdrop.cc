#include "backdrop.h"

#include "graphics.h"

Backdrop::Backdrop(Graphics&, const std::string& file) {
  this->file = file;
}

void Backdrop::draw(Graphics& graphics) {
  graphics.blit(file, NULL, NULL);
}
