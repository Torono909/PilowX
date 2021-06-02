#include "slider.h"

#include <ncurses.h>
#include <string>
#include "../utils/utils.h"

Slider::Slider(const char *name, int min, int max, int defaultVal) {
  this->min = min;
  this->max = max;
  current = defaultVal;
  this->name = name;
}

void Slider::render(int x, int y, int width) {
  mvaddstr(y, x, name);
  mvaddstr(y + 2, x, std::to_string(min).c_str());
  drawBox(x + 2, y + 1, width - 4);
  mvaddstr(y + 2, x + width, std::to_string(max).c_str());
}

void Slider::drawBox(int x, int y, int width) {
  mvaddch(y + 1, x, '|');
  mvaddch(y + 1, x + width, '|');

  for (int i = 0; i < width - 1; i++) {
    mvaddstr(y, x + 1 + i, "-");
    mvaddch(y + 2, x  + 1 + i, '-');
  }

  float partial = ((float)(current - min)) / ((float)(max - min));
  int stars = (width - 2) * partial;

  for (int i = 0; i < stars; i++) {
    mvaddch(y + 1, x + 1 + i, '*');
  }
}

int Slider::getMax() {
  return max;
}

int Slider::getMin() {
  return min;
}

int Slider::getCurrent() {
  return current;
}

void Slider::setCurrent(int current) {
  this->current = current;
}
